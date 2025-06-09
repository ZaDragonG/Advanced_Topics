import pandas as pd
import matplotlib.pyplot as plt

# Load data
rtos_df = pd.read_csv("Augmented-FreeRTOS/benchmark_results.csv")
gpos_df = pd.read_csv("benchmark_results_gpos.csv")


rtos_df['ms_smooth'] = rtos_df['ms'].rolling(window=10).mean()
gpos_df['ms_smooth'] = gpos_df['ms'].rolling(window=10).mean()


plt.figure(figsize=(10, 6))
plt.plot(rtos_df['batch_size'], rtos_df['ms_smooth'], label='RTOS (smoothed)', color='blue', linewidth=2)
plt.plot(gpos_df['batch_size'], gpos_df['ms_smooth'], label='GPOS (smoothed)', color='orange', linewidth=2)
plt.title("Execution Time vs Batch Size (Smoothed)", fontsize=14)
plt.xlabel("Batch Size", fontsize=12)
plt.ylabel("Execution Time (ms)", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("1_execution_time_smoothed.png", dpi=300)


rtos_df['jitter'] = rtos_df['ms'].diff().abs()
gpos_df['jitter'] = gpos_df['ms'].diff().abs()


plt.figure(figsize=(10, 6))
plt.scatter(rtos_df['run_number'], rtos_df['jitter'], label='RTOS Jitter', color='blue', s=10, alpha=0.6)
plt.scatter(gpos_df['run_number'], gpos_df['jitter'], label='GPOS Jitter', color='orange', s=10, alpha=0.6)
plt.title("Jitter: Change in Execution Time per Run", fontsize=14)
plt.xlabel("Run Number", fontsize=12)
plt.ylabel("Jitter (ms)", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("2_jitter_vs_run_dotplot.png", dpi=300)



speedup = gpos_df['ms'] / rtos_df['ms']
plt.figure(figsize=(10, 6))
plt.scatter(gpos_df['batch_size'], speedup, label='GPOS / RTOS Time Ratio', color='black', s=10)
plt.axhline(y=1.0, color='gray', linestyle='--', linewidth=1)
plt.title("Relative Performance: GPOS / RTOS Execution Time", fontsize=14)
plt.xlabel("Batch Size", fontsize=12)
plt.ylabel("Speedup Ratio", fontsize=12)
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend(fontsize=10)
plt.tight_layout()
plt.savefig("3_speedup_ratio_dotplot.png", dpi=300)


plt.show()
