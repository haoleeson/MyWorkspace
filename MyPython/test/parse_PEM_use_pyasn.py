#!/usr/bin/env python3

# 解析 PEM 证书
# Usage: python3 parse_PEM_use_pyasn1.py ./ca.crt.pem

import sys, os
from pyasn1_modules import pem, rfc2459
from pyasn1.codec.der import decoder

def main(*argv):
    if (len(sys.argv) > 1 and len(sys.argv[1]) > 0):
            print("main() argv[1] = %s"%sys.argv[1])
    cert_file_base_name = (sys.argv[1] if (len(sys.argv) > 1 and len(sys.argv[1]) > 0) else "")
    # substrate = pem.readPemFromFile(open('cert.pem'))
    # substrate = pem.readPemFromFile(open('./ca.crt.pem')) # success
    substrate = pem.readPemFromFile(open(cert_file_base_name))
    # substrate = pem.readPemFromFile(open("./ca.crt.pem"))
    cert = decoder.decode(substrate, asn1Spec=rfc2459.Certificate())[0]
    print(cert.prettyPrint())

if __name__ == "__main__":
    main()