import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

def load_and_analyze_data():
    """Загрузка и анализ результатов"""
    try:
        df = pd.read_csv('sorting_performance_results.csv')
        return df
    except FileNotFoundError:
        print("File 'sorting_performance_results.csv' not found. Run the C++ program first.")
        return None

def create_performance_plots(df):
    """Создание графиков производительности"""
    if df is None:
        return
    
    # Настройка стиля
    plt.style.use('seaborn-v0_8')
    sns.set_palette("husl")
    
    data_types = df['DataType'].unique()
    algorithms = df['Algorithm'].unique()
    
    # График 1: Общее сравнение по типам данных
    fig, axes = plt.subplots(2, 3, figsize=(18, 12))
    axes = axes.flatten()
    
    for i, data_type in enumerate(data_types):
        if i >= len(axes):
            break
            
        data_subset = df[df['DataType'] == data_type]
        
        for algo in algorithms:
            algo_data = data_subset[data_subset['Algorithm'] == algo]
            axes[i].plot(algo_data['Size'], algo_data['TimeMs'], 
                        marker='o', label=algo, linewidth=2)
        
        axes[i].set_title(f'{data_type} Data', fontsize=14, fontweight='bold')
        axes[i].set_xlabel('Array Size')
        axes[i].set_ylabel('Time (ms)')
        axes[i].legend()
        axes[i].grid(True, alpha=0.3)
        axes[i].set_xscale('log')
        axes[i].set_yscale('log')
    
    # Удаляем лишние subplots
    for j in range(len(data_types), len(axes)):
        fig.delaxes(axes[j])
    
    plt.tight_layout()
    plt.savefig('performance_comparison.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    # График 2: Отношение времени выполнения (Hybrid/Standard)
    fig, ax = plt.subplots(figsize=(12, 8))
    
    for data_type in data_types:
        ratio_data = []
        sizes = []
        
        for size in df['Size'].unique():
            standard_time = df[(df['DataType'] == data_type) & 
                             (df['Algorithm'] == 'QuickSort_Standard') & 
                             (df['Size'] == size)]['TimeMs'].values
            hybrid_time = df[(df['DataType'] == data_type) & 
                           (df['Algorithm'] == 'QuickSort_Hybrid') & 
                           (df['Size'] == size)]['TimeMs'].values
            
            if len(standard_time) > 0 and len(hybrid_time) > 0 and standard_time[0] > 0:
                ratio = hybrid_time[0] / standard_time[0]
                ratio_data.append(ratio)
                sizes.append(size)
        
        ax.plot(sizes, ratio_data, marker='s', label=data_type, linewidth=2)
    
    ax.axhline(y=1.0, color='red', linestyle='--', alpha=0.7, label='Equal Performance')
    ax.set_title('Performance Ratio: Hybrid/Standard QuickSort', fontsize=16, fontweight='bold')
    ax.set_xlabel('Array Size')
    ax.set_ylabel('Time Ratio (Hybrid/Standard)')
    ax.legend()
    ax.grid(True, alpha=0.3)
    ax.set_xscale('log')
    plt.tight_layout()
    plt.savefig('performance_ratio.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    # График 3: Абсолютное время для больших массивов
    large_data = df[df['Size'] >= 10000]
    plt.figure(figsize=(14, 8))
    
    for data_type in data_types:
        for algo in algorithms:
            subset = large_data[(large_data['DataType'] == data_type) & 
                              (large_data['Algorithm'] == algo)]
            if not subset.empty:
                plt.plot(subset['Size'], subset['TimeMs'], 
                        marker='o', linewidth=2, 
                        label=f'{algo} - {data_type}')
    
    plt.title('Performance on Large Arrays (n ≥ 10,000)', fontsize=16, fontweight='bold')
    plt.xlabel('Array Size')
    plt.ylabel('Time (ms)')
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.grid(True, alpha=0.3)
    plt.xscale('log')
    plt.yscale('log')
    plt.tight_layout()
    plt.savefig('large_arrays_performance.png', dpi=300, bbox_inches='tight')
    plt.show()

def print_statistical_summary(df):
    """Вывод статистической сводки"""
    print("=== STATISTICAL SUMMARY ===")
    
    # Среднее время по алгоритмам и типам данных
    summary = df.groupby(['Algorithm', 'DataType'])['TimeMs'].agg(['mean', 'std', 'min', 'max'])
    print("\nAverage Performance (ms):")
    print(summary.round(2))
    
    # Сравнение производительности
    print("\n=== PERFORMANCE COMPARISON ===")
    for data_type in df['DataType'].unique():
        standard_times = df[(df['DataType'] == data_type) & 
                          (df['Algorithm'] == 'QuickSort_Standard')]['TimeMs']
        hybrid_times = df[(df['DataType'] == data_type) & 
                        (df['Algorithm'] == 'QuickSort_Hybrid')]['TimeMs']
        
        if len(standard_times) > 0 and len(hybrid_times) > 0:
            avg_standard = standard_times.mean()
            avg_hybrid = hybrid_times.mean()
            improvement = ((avg_standard - avg_hybrid) / avg_standard) * 100
            
            print(f"{data_type}:")
            print(f"  Standard: {avg_standard:.2f}ms")
            print(f"  Hybrid: {avg_hybrid:.2f}ms")
            print(f"  Improvement: {improvement:+.2f}%")
            print()

def main():
    """Основная функция"""
    print("Loading and analyzing sorting performance data...")
    
    df = load_and_analyze_data()
    
    if df is not None:
        print(f"Loaded {len(df)} test results")
        print(f"Data types: {df['DataType'].unique()}")
        print(f"Algorithms: {df['Algorithm'].unique()}")
        print(f"Array sizes: {sorted(df['Size'].unique())}")
        
        # Создание графиков
        create_performance_plots(df)
        
        # Статистическая сводка
        print_statistical_summary(df)
        
        print("Analysis complete! Check the generated PNG files for visualizations.")

if __name__ == "__main__":
    main()