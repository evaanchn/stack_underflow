""" Program purpose """
import sys
import partition

def main():
    """ Start program execution """
    memo = {}
    print(partition.min_coins_topdown([1, 2, 5], 11, memo))

if __name__ == '__main__':
    main()
