import csv
import statistics


# Use the statistics library to perform calculations & round their values to x digits.
def mean(data: list):
    return round(statistics.mean(data), 4)

def variance(data: list):
    return round(statistics.variance(data), 4)

def std_dev(data: list):
    return round(statistics.stdev(data), 4)


def main():
    open_prices  = []
    high_prices  = []
    low_prices   = []
    close_prices = []

    with open('2025_aapl_data.csv', 'r') as file:
        reader = csv.reader(file)
        headers = next(reader)

        for row in reader:  # loop through the data
            date, open_price, high, low, close, volume,  = row[0], row[1], row[2], row[3], row[4], row[5]
            open_prices.append(float(open_price))
            high_prices.append(float(high))
            low_prices.append(float(low))
            close_prices.append(float(close))
    file.close()
    
    # Perform calculations & print results
    print("|==========================================================|")
    print("|          |    Open   |    High   |     Low   |   Close   |")
    print("|==========================================================|")
    print("|     Mean |%11f|%11f|%11f|%11f|" % (mean(open_prices), mean(high_prices), mean(low_prices), mean(close_prices)))
    print("|----------------------------------------------------------|")
    print("| Variance |%11f|%11f|%11f|%11f|" % (variance(open_prices),variance(high_prices),variance(low_prices),variance(close_prices)))
    print("|----------------------------------------------------------|")
    print("| Std. Dev |%11f|%11f|%11f|%11f|" % (std_dev(open_prices),std_dev(high_prices),std_dev(low_prices),std_dev(close_prices)))
    print("|==========================================================|\n")


if __name__=='__main__':
    main()
