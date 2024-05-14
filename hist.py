import subprocess
import numpy as np
import matplotlib.pyplot as plt

def run_ball_samp_cpu():
    command = "./ball_samp-cpu"
    process = subprocess.Popen(command, stdout=subprocess.PIPE)
    output, _ = process.communicate()
    return output.decode("utf-8")

def parse_histogram(output):
    histograms = []
    lines = output.strip().split('\n')
    for line in lines:
        if line.startswith("Dimension:"):
            dim = int(line.split(":")[1])
            histograms.append({"dim": dim, "values": []})
        else:
            data = list(map(float, line.split()))
            histograms[-1]["values"].extend(data)
    return histograms

def plot_histograms(histograms):
    for hist in histograms:
        dim = hist["dim"]
        values = hist["values"]
        num_bins = len(values)
        distances = np.linspace(0, 1, num_bins)
        plt.plot(distances, values, label=f"Dimension {dim}")
    plt.xlabel("Distance from Surface")
    plt.ylabel("Fraction of Volume")
    plt.title("Histograms of Distance from Surface")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    output = run_ball_samp_cpu()
    histograms = parse_histogram(output)
    plot_histograms(histograms)
