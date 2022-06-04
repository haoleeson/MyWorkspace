#!/usr/bin/env python3

# 解析 X.509 证书明文内容
# Usage: parse_x509_use_ssl.py ./client.crt

import sys
import os
import ssl
import pprint


def main(*argv):
    # cert_file_base_name = "./ca.crt.pem" # success
    # cert_file_base_name = "./server.crt" # success
    # cert_file_base_name = "./client.crt" # success
    # if (len(sys.argv) > 1 and len(sys.argv[0]) > 0):
    #     print("main() argv[1] = %s"%sys.argv[1])
    cert_file_base_name = (sys.argv[1] if (len(sys.argv) > 1 and len(sys.argv[0]) > 0) else "" )
    # print("cert_file_base_name: %s"%cert_file_base_name)
    cert_file_name = os.path.join(os.path.dirname(__file__), cert_file_base_name)
    try:
        cert_dict = ssl._ssl._test_decode_cert(cert_file_name)
    except Exception as e:
        print("Error decoding certificate: {0:}".format(e))
    else:
        print("Certificate ({0:s}) data:\n".format(cert_file_base_name))
        pprint.pprint(cert_dict)


if __name__ == "__main__":
    print("Python {0:s} {1:d}bit on {2:s}\n".format(" ".join(item.strip() for item in sys.version.split("\n")), 64 if sys.maxsize > 0x100000000 else 32, sys.platform))
    # if len(sys.argv) > 1 and len(sys.argv[1]) > 0:
    #     print("argv[1] = %s"%sys.argv[1])
    rc = main(sys.argv[1:])
    print("rc[0]:%s"%rc)
    print("\nDone.")
    sys.exit(rc)