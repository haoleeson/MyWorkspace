#!/bin/bash

# OpenWrt Time Synchronization Script
# Direct time setting only - No NTP

# Configuration - Edit these variables for your environment
ROUTER_IP="192.168.1.1"           # OpenWrt router IP address
ROUTER_USER="root"                # SSH username
ROUTER_PASSWORD="your_password"   # SSH password
SSH_PORT="22"                     # SSH port
TIMEZONE="UTC+8‌‌"                  # OpenWrt timezone

# Color definitions for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Logging functions
log() {
    echo -e "${GREEN}[$(date '+%Y-%m-%d %H:%M:%S')] INFO:${NC} $1"
}

error() {
    echo -e "${RED}[$(date '+%Y-%m-%d %H:%M:%S')] ERROR:${NC} $1"
}

# Validate configuration
validate_config() {
    if [[ -z "$ROUTER_IP" ]]; then
        error "ROUTER_IP is not set"
        return 1
    fi
    
    if [[ -z "$ROUTER_USER" ]]; then
        error "ROUTER_USER is not set"
        return 1
    fi
    
    if [[ -z "$ROUTER_PASSWORD" ]]; then
        error "ROUTER_PASSWORD is not set"
        return 1
    fi
    
    return 0
}

# Check dependencies
check_dependencies() {
    if ! command -v ssh &> /dev/null; then
        error "SSH client is not installed"
        return 1
    fi
    
    if ! command -v sshpass &> /dev/null; then
        error "sshpass is required but not installed"
        return 1
    fi
    
    return 0
}

# Check SSH connectivity
check_ssh_connectivity() {
    log "Testing SSH connection to ${ROUTER_USER}@${ROUTER_IP}"
    
    if sshpass -p "$ROUTER_PASSWORD" ssh -o ConnectTimeout=5 -o StrictHostKeyChecking=no \
        -p $SSH_PORT ${ROUTER_USER}@${ROUTER_IP} "echo 'Connected'" &> /dev/null; then
        log "SSH connection successful"
        return 0
    else
        error "SSH connection failed"
        return 1
    fi
}

# Execute command on OpenWrt via SSH
ssh_exec() {
    local cmd="$1"
    sshpass -p "$ROUTER_PASSWORD" ssh -o ConnectTimeout=10 -o StrictHostKeyChecking=no \
        -p $SSH_PORT ${ROUTER_USER}@${ROUTER_IP} "$cmd"
}

# Get formatted local time
get_local_time() {
    date '+%Y-%m-%d %H:%M:%S'
}

# Synchronize time with OpenWrt device
sync_time() {
    log "Starting time synchronization"
    
    local local_time=$(get_local_time)
    log "Local time: $local_time"
    
    # Set OpenWrt timezone if specified
    if [[ -n "$TIMEZONE" ]]; then
        log "Setting timezone: $TIMEZONE"
        if ssh_exec "uci set system.@system[0].timezone='$TIMEZONE' && uci commit system"; then
            log "Timezone configured successfully"
        else
            error "Failed to set timezone"
        fi
    fi
    
    # Sync system time
    log "Setting system time on OpenWrt device"
    if ssh_exec "date -s '$local_time'"; then
        log "Time synchronized successfully"
    else
        error "Time synchronization failed"
        return 1
    fi
    
    # Update hardware clock if available
    log "Updating hardware clock"
    ssh_exec "hwclock -w || echo 'Hardware clock update not supported'"
    
    return 0
}

# Display synchronization results
show_results() {
    log "=== Synchronization Results ==="
    log "Device: ${ROUTER_USER}@${ROUTER_IP}"
    log "Local time: $(get_local_time)"
    log "Remote time: $(ssh_exec "date '+%Y-%m-%d %H:%M:%S'")"
    log "Remote timezone: $(ssh_exec "uci get system.@system[0].timezone 2>/dev/null || echo 'Not set'")"
    log "==============================="
}

# Main execution function
main() {
    log "OpenWrt Time Synchronization Started"
    
    # Validate configuration
    if ! validate_config; then
        error "Configuration validation failed"
        exit 1
    fi
    
    # Check dependencies
    if ! check_dependencies; then
        error "Dependency check failed"
        exit 1
    fi
    
    # Test SSH connectivity
    if ! check_ssh_connectivity; then
        error "Cannot establish SSH connection"
        exit 1
    fi
    
    # Perform time synchronization
    if sync_time; then
        log "Time synchronization successful"
        show_results
    else
        error "Time synchronization failed"
        exit 1
    fi
    
    log "Time synchronization completed"
}

# Execute main function
main
