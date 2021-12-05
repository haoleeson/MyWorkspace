import logging.handlers
import sys
import optparse

# sets variable 'optcfg'
def get_cmdline_opts():
    optcfg = optparse.OptionParser(usage='usage: %s [-a/--option_a][-b/--option_b]' % sys.argv[0])
    optcfg.add_option('-a', '--option_a', dest='a', type='string', default='A_DEFAULT_STR', help='input opt a')
    optcfg.add_option('-b', '--option_b', dest='b', type='string', default='B_DEFAULT_STR', help='input opt b')
    optcfg.add_option('-p', '--port', dest='port', type='int', help='port')
    return optcfg.parse_args()

def main():
    (opts, args) = get_cmdline_opts()
    a_opt = opts.a
    b_opt = opts.b
    p_opt = opts.port

    print('The input value of opt a is: ' + a_opt)
    print('The input value of opt b is: ' + b_opt)
    print('The input value of opt p is: ' + str(p_opt))
    print('The input value of args is: ')
    print(args)

if __name__ == "__main__":
    main()

# 执行示例：
# python3 ./test_getopt.py -a aaa
# python3 ./test_getopt.py -b bbb
# python3 ./test_getopt.py --option_a AAA
# python3 ./test_getopt.py --option_b BBB
# python3 ./test_getopt.py -a aaa --option_a AAA
# python3 ./test_getopt.py --option_a AAA -a aaa
# python3 ./test_getopt.py -a aaa -b bbb
