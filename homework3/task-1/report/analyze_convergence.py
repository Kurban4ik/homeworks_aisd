import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def analyze_convergence():
    wide_data = pd.read_csv('wide_area_results.csv')
    narrow_data = pd.read_csv('narrow_area_results.csv')
    exact_area = 0.25 * np.pi + 1.25 * np.arcsin(0.8) - 1
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
    
    theoretical_conv = 100 / np.sqrt(wide_data['N'])
    
    ax1.plot(wide_data['N'], wide_data['RelativeError'] * 100, 
             'b-', label='Wide Area', alpha=0.7)
    ax1.plot(wide_data['N'], theoretical_conv, 'k--', 
             label='Theoretical O(1/√N)', alpha=0.7)
    ax1.set_xlabel('Number of points (N)')
    ax1.set_ylabel('Relative Error (%)')
    ax1.set_title('Wide Area: Convergence Analysis')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    ax1.set_yscale('log')
    ax1.set_xscale('log')
    
    ax2.plot(narrow_data['N'], narrow_data['RelativeError'] * 100, 
             'r-', label='Narrow Area', alpha=0.7)
    ax2.plot(narrow_data['N'], theoretical_conv, 'k--', 
             label='Theoretical O(1/√N)', alpha=0.7)
    ax2.set_xlabel('Number of points (N)')
    ax2.set_ylabel('Relative Error (%)')
    ax2.set_title('Narrow Area: Convergence Analysis')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    ax2.set_yscale('log')
    ax2.set_xscale('log')
    
    plt.tight_layout()
    plt.savefig('convergence_analysis.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    plt.figure(figsize=(10, 6))
    plt.plot(wide_data['N'], wide_data['TimeMs'], 'b-', 
             label='Wide Area', alpha=0.7)
    plt.plot(narrow_data['N'], narrow_data['TimeMs'], 'r-', 
             label='Narrow Area', alpha=0.7)
    plt.xlabel('Number of points (N)')
    plt.ylabel('Execution Time (ms)')
    plt.title('Computational Time vs Number of Points')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.savefig('computation_time.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    analyze_convergence()