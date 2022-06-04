#!/usr/bin/env python

def isNone(data):
    return True if data == None else False

def isEmpty(data):
    return True if data == '' else False

def test(data):
    if isNone(data):
        print('isNone: True')
    else:
        print('isNone: False')
    if isEmpty(data):
        print('isEmpty: True')
    else:
        print('isEmpty: False')
    
def main():
    none_val = None
    empty_val = ''
    print('test none val:')
    test(none_val)
    print('test empty val:')
    test(empty_val)

if __name__ == "__main__":
    main()