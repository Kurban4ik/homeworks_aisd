import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

exact_area = 0.25 * np.pi + 1.25 * np.arcsin(0.8) - 1

def plot_results():
    wide_data = pd.read_csv('wide_area_results.csv')
    narrow_data = pd.read_csv('narrow_area_results.csv')
    
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 10))
    
    ax1.plot(wide_data['N'], wide_data['ApproximateArea'], 
             'b-', alpha=0.7, label='Monte Carlo')
    ax1.axhline(y=exact_area, color='r', linestyle='--', 
                label=f'Exact area: {exact_area:.6f}')
    ax1.set_xlabel('Number of points (N)')
    ax1.set_ylabel('Approximate Area')
    ax1.set_title('Wide Area: Approximate Area vs N')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    ax2.plot(wide_data['N'], wide_data['RelativeError'] * 100, 
             'r-', alpha=0.7)
    ax2.set_xlabel('Number of points (N)')
    ax2.set_ylabel('Relative Error (%)')
    ax2.set_title('Wide Area: Relative Error vs N')
    ax2.grid(True, alpha=0.3)
    ax2.set_yscale('log')
    
    ax3.plot(narrow_data['N'], narrow_data['ApproximateArea'], 
             'g-', alpha=0.7, label='Monte Carlo')
    ax3.axhline(y=exact_area, color='r', linestyle='--', 
                label=f'Exact area: {exact_area:.6f}')
    ax3.set_xlabel('Number of points (N)')
    ax3.set_ylabel('Approximate Area')
    ax3.set_title('Narrow Area: Approximate Area vs N')
    ax3.legend()
    ax3.grid(True, alpha=0.3)
    
    ax4.plot(narrow_data['N'], narrow_data['RelativeError'] * 100, 
             'm-', alpha=0.7)
    ax4.set_xlabel('Number of points (N)')
    ax4.set_ylabel('Relative Error (%)')
    ax4.set_title('Narrow Area: Relative Error vs N')
    ax4.grid(True, alpha=0.3)
    ax4.set_yscale('log')
    
    plt.tight_layout()
    plt.savefig('monte_carlo_results.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    plt.figure(figsize=(10, 6))
    plt.plot(wide_data['N'], wide_data['RelativeError'] * 100, 
             'b-', label='Wide Area', alpha=0.7)
    plt.plot(narrow_data['N'], narrow_data['RelativeError'] * 100, 
             'r-', label='Narrow Area', alpha=0.7)
    plt.xlabel('Number of points (N)')
    plt.ylabel('Relative Error (%)')
    plt.title('Comparison of Relative Errors')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.yscale('log')
    plt.savefig('error_comparison.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    print("Final Results:")
    print(f"Exact area: {exact_area:.6f}")
    print(f"Wide area final approximation: {wide_data['ApproximateArea'].iloc[-1]:.6f}")
    print(f"Wide area final error: {wide_data['RelativeError'].iloc[-1]*100:.4f}%")
    print(f"Narrow area final approximation: {narrow_data['ApproximateArea'].iloc[-1]:.6f}")
    print(f"Narrow area final error: {narrow_data['RelativeError'].iloc[-1]*100:.4f}%")

if __name__ == "__main__":
    plot_results()