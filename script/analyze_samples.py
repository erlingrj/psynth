import csv
import matplotlib.pyplot as plt

# Read samples from the CSV file
samples = []
with open('sample_log.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        samples.append(float(row[0]))

# Plot the samples
plt.figure(figsize=(10, 6))
plt.plot(samples, label='Audio Samples')
plt.title('Audio Samples Visualization')
plt.xlabel('Sample Index')
plt.ylabel('Amplitude')
plt.legend()
plt.grid(True)
plt.show()