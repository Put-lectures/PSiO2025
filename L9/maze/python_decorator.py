import time
def timeit(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print(f"Duration: {end - start} seconds")
        return result
    return wrapper

@timeit
def my_funct():
    print(list(range(10)))



if __name__ == "__main__":
    my_funct()
    # timeit(my_funct)
 