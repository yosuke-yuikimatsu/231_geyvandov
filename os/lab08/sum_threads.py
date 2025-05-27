import sys
import random
import threading


def main():
    try:
        N = int(sys.stdin.readline())
    except Exception:
        return
    if N < 16:
        return

    a = [random.randint(0, 999) for _ in range(N)]
    print("Array:", *a)

    lock = threading.Lock()
    total = 0

    def worker(s, e):
        nonlocal total
        local_sum = sum(a[s:e])
        with lock:
            total += local_sum

    base = N // 4
    rem = N % 4
    idx = 0
    threads = []
    for i in range(4):
        ln = base + (1 if i < rem else 0)
        t = threading.Thread(target=worker, args=(idx, idx + ln))
        t.start()
        threads.append(t)
        idx += ln

    for t in threads:
        t.join()

    print("Total sum:", total)


if __name__ == "__main__":
    main()
