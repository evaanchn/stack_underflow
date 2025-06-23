""" Copyright Sergio Moya Valerin, ejemplo de clase CI-0116 """

""" min coins dp """
def min_coins_topdown(coins, amount, memo=None):
    if amount in memo:
        return memo[amount]
    if amount == 0:
        return 0
    if amount < 0:
        return float('inf')

    min_coins = float('inf')
    for coin in coins:
        res = min_coins_topdown(coins, amount - coin, memo)
        if res != float('inf'):
            min_coins = min(min_coins, res + 1)
    
    memo[amount] = min_coins
    return min_coins
