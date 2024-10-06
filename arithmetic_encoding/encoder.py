class ArithmeticEncoder:
    def __init__(self, symbols, probabilities):
        self.symbols = symbols
        self.probabilities = probabilities
        self.cumulative_probabilities = self.calculate_cumulative_probabilities()

    def calculate_cumulative_probabilities(self):
        cumulative_prob = {}
        cumulative = 0
        
        for symbol, prob in zip(self.symbols, self.probabilities):
            
            cumulative_prob[symbol] = (cumulative, cumulative + prob)
            cumulative += prob
            # print(f"Symbol: {symbol}, Prob: {prob} Cumulative Prob: {cumulative_prob[symbol]}")
        return cumulative_prob

    def encode(self, codeword):
        low = 0
        high = 1
        intervals = []

        for symbol in codeword:
            low_range, high_range = self.cumulative_probabilities[symbol]
            range_size = high - low
            # print(f"low range: {low_range} high range: {high_range} symbol: {symbol}")
            high = low + (range_size * high_range)
            low = low + (range_size * low_range)
            
            # high = low + range_size
            # print(f"low: {low} high: {high} symbol: {symbol}")
            intervals.append((low, high))
            # print("----------------------------------")

        return intervals


def main():
    symbols = ['1', '2', '3']
    probabilities = [0.4, 0.4, 0.2]     

    encoder = ArithmeticEncoder(symbols, probabilities)

    codeword = "1312"
    intervals = encoder.encode(codeword)

    print(f"Inital Interval:     (0, 1)")
    for symbol, interval in zip(codeword, intervals):
        print(f"Symbol: {symbol}, Interval: {interval}")


if __name__ == "__main__":
    main()
