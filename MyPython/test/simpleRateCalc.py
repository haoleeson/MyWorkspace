#!/usr/bin/env python
import math

def calculate_rate(principal: int, apr: float, year: int):
    '''
    calculate rate
    @param  principal   principal
    @param  apr         Average Prime Rate(%)
    @param  year        Holding Time
    '''
    def rate(principal: int, apr: float, year: int) -> (int, float):
        all_rate = math.pow((apr / 100 + 1.0), year)
        earn = principal * all_rate - principal
        earn_rate = all_rate * 100 - 100
        return earn, earn_rate

    print("====== total earn: %d, rate: %.2f percent ======\n" % rate(principal, apr, year))
    # output rate of every year
    for i in range(year):
        t_earn, t_earn_rate = rate(principal, apr, i + 1)
        print("  the {} year,\tearn: {:,.0f}\trate: {:,.2f} percent".format(i + 1, t_earn, t_earn_rate))


def main():
    print('hello')
    # principal
    principal = 1e5
    # Average Prime Rate (%)
    apr = 3.05
    # year
    year = 40

    calculate_rate(principal, apr, year)


if __name__ == "__main__":
    main()
