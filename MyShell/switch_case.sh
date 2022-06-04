#!/usr/bin/env bash

func_test_switch() {
    param1="$1"
    case "$param1" in
        "A"|"B")
            echo "ABAB"
            ;;
        "C")
            echo "CCCC"
            ;;
        *)
            echo "DEFAULT"
            ;;
    esac
}

main() {
    func_test_switch 'A'
    func_test_switch 'B'
    func_test_switch 'C'
    func_test_switch 'xca'
}

main