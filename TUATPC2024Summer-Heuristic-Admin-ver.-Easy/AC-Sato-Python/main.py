#!/usr/local/bin/pypy3

def main():
    n = int(input())
    all_users_rating_max = 0
    max_sum = 0

    a = list(map(int, input().split()))
    h = list(map(int, input().split()))

    for i in range(n):
        this_user_max = max(a[i], h[i])
        all_users_rating_max = max(all_users_rating_max, this_user_max)
        max_sum += this_user_max

    if n == 1 or n == 2 or all_users_rating_max < 1600 or max_sum < 4200:
        print("Yes")
    else:
        print("No")

if __name__ == "__main__":
    main()
