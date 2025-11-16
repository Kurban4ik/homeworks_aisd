import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
from pathlib import Path

plt.style.use('seaborn-v0_8')
sns.set_palette("husl")
def plot_detailed_threshold_analysis():
    """Детальный анализ порога с учетом статистики"""
    try:
        threshold_df = pd.read_csv('threshold_test.csv')
        
        fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))
        
        # Основной график с медианой/средним
        if 'MedianTime' in threshold_df.columns:
            main_time = 'MedianTime'
            ax1.plot(threshold_df['Threshold'], threshold_df['MedianTime'], 'o-', 
                    linewidth=3, markersize=8, label='Медианное время', color='blue')
        else:
            main_time = 'Time'
            ax1.plot(threshold_df['Threshold'], threshold_df['Time'], 'o-', 
                    linewidth=3, markersize=8, label='Среднее время', color='blue')
        
        if 'MinTime' in threshold_df.columns and 'MaxTime' in threshold_df.columns:
            ax1.fill_between(threshold_df['Threshold'], 
                           threshold_df['MinTime'], 
                           threshold_df['MaxTime'], 
                           alpha=0.2, label='Диапазон min-max', color='blue')
        
        ax1.set_title('Зависимость времени выполнения от порога переключения\n(10 запусков для каждого порога)', 
                     fontsize=14, fontweight='bold')
        ax1.set_xlabel('Порог переключения (количество элементов)')
        ax1.set_ylabel('Время выполнения (микросекунды)')
        ax1.grid(True, alpha=0.3)
        ax1.legend()
        
        optimal_idx = threshold_df[main_time].idxmin()
        optimal_threshold = threshold_df.loc[optimal_idx, 'Threshold']
        optimal_time = threshold_df.loc[optimal_idx, main_time]
        
        ax1.axvline(x=optimal_threshold, color='red', linestyle='--', alpha=0.7, 
                   label=f'Оптимальный порог: {optimal_threshold}')
        
        if 'StdDev' in threshold_df.columns:
            ax2.bar(threshold_df['Threshold'], threshold_df['StdDev'], 
                   alpha=0.7, color='orange')
            ax2.set_title('Стандартное отклонение времени выполнения')
            ax2.set_xlabel('Порог переключения (количество элементов)')
            ax2.set_ylabel('Стандартное отклонение (микросекунды)')
            ax2.grid(True, alpha=0.3)
        
        plt.tight_layout()
        plt.savefig('detailed_threshold_analysis.png', dpi=300, bbox_inches='tight')
        plt.show()
        
        print(f"Оптимальный порог переключения: {optimal_threshold}")
        print(f"Минимальное время выполнения: {optimal_time} микросекунд")
        
    except FileNotFoundError:
        print("Файл threshold_test.csv не найден")
def plot_comparison():
    """Сравнение стандартного и гибридного алгоритмов"""
    fig, axes = plt.subplots(2, 3, figsize=(18, 12))
    fig.suptitle('Сравнение производительности Merge Sort и Hybrid Merge Sort', fontsize=16, fontweight='bold')
    
    data_types = ['random', 'reverse', 'almost']
    titles = {
        'random': 'Случайные данные',
        'reverse': 'Обратно отсортированные данные', 
        'almost': 'Почти отсортированные данные'
    }
    
    for i, data_type in enumerate(data_types):
        try:
            standard_df = pd.read_csv(f'standard_{data_type}.csv')
            hybrid_df = pd.read_csv(f'hybrid_{data_type}.csv')
            
            ax1 = axes[0, i]
            ax1.plot(standard_df['Size'], standard_df['Time'], 'b-', label='Standard Merge Sort', linewidth=2)
            ax1.plot(hybrid_df['Size'], hybrid_df['Time'], 'r-', label='Hybrid Merge Sort (threshold=10)', linewidth=2)
            ax1.set_title(f'{titles[data_type]}', fontweight='bold')
            ax1.set_xlabel('Размер массива')
            ax1.set_ylabel('Время (микросекунды)')
            ax1.legend()
            ax1.grid(True, alpha=0.3)
            
            # График ускорения
            ax2 = axes[1, i]
            speedup = (standard_df['Time'] - hybrid_df['Time']) / standard_df['Time'] * 100
            ax2.plot(standard_df['Size'], speedup, 'g-', linewidth=2)
            ax2.set_title(f'Ускорение гибридного алгоритма\n({titles[data_type]})')
            ax2.set_xlabel('Размер массива')
            ax2.set_ylabel('Ускорение (%)')
            ax2.grid(True, alpha=0.3)
            ax2.axhline(y=0, color='k', linestyle='--', alpha=0.5)
            
        except FileNotFoundError:
            print(f"Файлы для {data_type} не найдены")
            continue
    
    plt.tight_layout()
    plt.savefig('comparison_results.png', dpi=300, bbox_inches='tight')
    plt.show()

def plot_individual_algorithms():
    """Отдельные графики для каждого алгоритма"""
    fig, axes = plt.subplots(2, 3, figsize=(18, 12))
    fig.suptitle('Производительность алгоритмов сортировки по типам данных', fontsize=16, fontweight='bold')
    
    data_types = ['random', 'reverse', 'almost']
    titles = {
        'random': 'Случайные данные',
        'reverse': 'Обратно отсортированные данные',
        'almost': 'Почти отсортированные данные'
    }
    
    for i, data_type in enumerate(data_types):
        try:
            standard_df = pd.read_csv(f'standard_{data_type}.csv')
            hybrid_df = pd.read_csv(f'hybrid_{data_type}.csv')
            
            ax1 = axes[0, i]
            ax1.plot(standard_df['Size'], standard_df['Time'], 'blue', linewidth=2)
            ax1.set_title(f'Standard Merge Sort\n({titles[data_type]})', fontweight='bold')
            ax1.set_xlabel('Размер массива')
            ax1.set_ylabel('Время (микросекунды)')
            ax1.grid(True, alpha=0.3)
            
            ax2 = axes[1, i]
            ax2.plot(hybrid_df['Size'], hybrid_df['Time'], 'red', linewidth=2)
            ax2.set_title(f'Hybrid Merge Sort\n({titles[data_type]})', fontweight='bold')
            ax2.set_xlabel('Размер массива')
            ax2.set_ylabel('Время (микросекунды)')
            ax2.grid(True, alpha=0.3)
            
        except FileNotFoundError:
            print(f"Файлы для {data_type} не найдены")
            continue
    
    plt.tight_layout()
    plt.savefig('individual_results.png', dpi=300, bbox_inches='tight')
    plt.show()

def plot_threshold_analysis():
    """Анализ оптимального порога переключения"""
    try:
        threshold_df = pd.read_csv('threshold_test.csv')
        
        plt.figure(figsize=(12, 8))
        plt.plot(threshold_df['Threshold'], threshold_df['Time'], 'o-', linewidth=3, markersize=8)
        plt.title('Зависимость времени выполнения от порога переключения\n(массив 10000 элементов)', fontsize=14, fontweight='bold')
        plt.xlabel('Порог переключения (количество элементов)')
        plt.ylabel('Время выполнения (микросекунды)')
        plt.grid(True, alpha=0.3)
        
        # Найдем оптимальный порог
        optimal_idx = threshold_df['Time'].idxmin()
        optimal_threshold = threshold_df.loc[optimal_idx, 'Threshold']
        optimal_time = threshold_df.loc[optimal_idx, 'Time']
        
        plt.axvline(x=optimal_threshold, color='red', linestyle='--', alpha=0.7, 
                   label=f'Оптимальный порог: {optimal_threshold}')
        plt.legend()
        
        plt.savefig('threshold_analysis.png', dpi=300, bbox_inches='tight')
        plt.show()
        
        print(f"Оптимальный порог переключения: {optimal_threshold}")
        print(f"Минимальное время выполнения: {optimal_time} микросекунд")
        
    except FileNotFoundError:
        print("Файл threshold_test.csv не найден")

def plot_log_scale():
    """Графики в логарифмическом масштабе"""
    fig, axes = plt.subplots(1, 3, figsize=(18, 6))
    fig.suptitle('Производительность алгоритмов (логарифмическая шкала)', fontsize=16, fontweight='bold')
    
    data_types = ['random', 'reverse', 'almost']
    titles = {
        'random': 'Случайные данные',
        'reverse': 'Обратно отсортированные данные',
        'almost': 'Почти отсортированные данные'
    }
    
    for i, data_type in enumerate(data_types):
        try:
            standard_df = pd.read_csv(f'standard_{data_type}.csv')
            hybrid_df = pd.read_csv(f'hybrid_{data_type}.csv')
            
            ax = axes[i]
            ax.loglog(standard_df['Size'], standard_df['Time'], 'b-', label='Standard Merge Sort', linewidth=2)
            ax.loglog(hybrid_df['Size'], hybrid_df['Time'], 'r-', label='Hybrid Merge Sort', linewidth=2)
            ax.set_title(f'{titles[data_type]}', fontweight='bold')
            ax.set_xlabel('Размер массива (log scale)')
            ax.set_ylabel('Время (log scale)')
            ax.legend()
            ax.grid(True, alpha=0.3, which='both')
            
        except FileNotFoundError:
            print(f"Файлы для {data_type} не найдены")
            continue
    
    plt.tight_layout()
    plt.savefig('log_scale_results.png', dpi=300, bbox_inches='tight')
    plt.show()

def generate_report():
    """Генерация текстового отчета"""
    report = []
    report.append("ОТЧЕТ ПО ЭКСПЕРИМЕНТАЛЬНОМУ ИССЛЕДОВАНИЮ АЛГОРИТМОВ СОРТИРОВКИ")
    report.append("=" * 70)
    report.append("\n")
    
    try:
        threshold_df = pd.read_csv('threshold_test.csv')
        optimal_idx = threshold_df['Time'].idxmin()
        optimal_threshold = threshold_df.loc[optimal_idx, 'Threshold']
        optimal_time = threshold_df.loc[optimal_idx, 'Time']
        
        report.append(f"ОПТИМАЛЬНЫЙ ПОРОГ ПЕРЕКЛЮЧЕНИЯ: {optimal_threshold} элементов")
        report.append(f"Минимальное время выполнения: {optimal_time} микросекунд")
        report.append("\n")
    except FileNotFoundError:
        report.append("Данные по анализу порога не найдены")
        report.append("\n")
    
    data_types = ['random', 'reverse', 'almost']
    type_names = {
        'random': 'случайные',
        'reverse': 'обратно отсортированные', 
        'almost': 'почти отсортированные'
    }
    
    report.append("СРАВНЕНИЕ ПРОИЗВОДИТЕЛЬНОСТИ ДЛЯ МАССИВА 100000 ЭЛЕМЕНТОВ:")
    report.append("-" * 70)
    
    for data_type in data_types:
        try:
            standard_df = pd.read_csv(f'standard_{data_type}.csv')
            hybrid_df = pd.read_csv(f'hybrid_{data_type}.csv')
            
            # Берем последние значения (максимальный размер)
            standard_time = standard_df['Time'].iloc[-1]
            hybrid_time = hybrid_df['Time'].iloc[-1]
            speedup = ((standard_time - hybrid_time) / standard_time) * 100
            
            report.append(f"{type_names[data_type].title()} данные:")
            report.append(f"  Standard Merge Sort: {standard_time:.2f} мкс")
            report.append(f"  Hybrid Merge Sort:   {hybrid_time:.2f} мкс")
            report.append(f"  Ускорение:           {speedup:+.2f}%")
            report.append("")
            
        except FileNotFoundError:
            report.append(f"Данные для {data_type} не найдены")
            report.append("")
    
    with open('experiment_report.txt', 'w', encoding='utf-8') as f:
        f.write('\n'.join(report))
    
    print("Отчет сохранен в файл experiment_report.txt")

if __name__ == "__main__":
    print("Генерация графиков...")
    
    # Создаем все графики
    plot_comparison()
    plot_individual_algorithms()
    plot_detailed_threshold_analysis()  # Заменяем старую функцию
    plot_log_scale()
    generate_report()
    
    print("Все графики сохранены в текущей директории:")
    print("- comparison_results.png: Сравнение алгоритмов")
    print("- individual_results.png: Отдельные графики для каждого алгоритма") 
    print("- detailed_threshold_analysis.png: Детальный анализ порога")
    print("- log_scale_results.png: Графики в логарифмическом масштабе")
    print("- experiment_report.txt: Текстовый отчет")