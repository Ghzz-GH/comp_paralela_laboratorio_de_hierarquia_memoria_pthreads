import pandas as pd
import matplotlib.pyplot as plt

plt.style.use('seaborn-v0_8-darkgrid')
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

caminho_excel = './documentos/tabelas_lab20260927.xlsx'

tabela2 = pd.read_excel(caminho_excel, sheet_name='tabela2')

algoritmos = tabela2['Algoritmo'].values
d1_miss_rate = (tabela2['D1 miss rate (%)'].values * 100).astype(float)

cores = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']
barras = ax1.bar(algoritmos, d1_miss_rate, color=cores, alpha=0.8, edgecolor='black', linewidth=1.5)

ax1.set_ylabel('D1 Miss Rate (%)', fontsize=12, fontweight='bold')
ax1.set_title('Taxa de Falta em L1 de Dados', fontsize=13, fontweight='bold')
ax1.set_ylim(0, max(d1_miss_rate) * 1.15)
ax1.grid(True, alpha=0.3, axis='y')

for barra, valor in zip(barras, d1_miss_rate):
    altura = barra.get_height()
    ax1.text(barra.get_x() + barra.get_width()/2., altura,
             f'{valor:.2f}%', ha='center', va='bottom', fontsize=10, fontweight='bold')

ax1.set_xticklabels(algoritmos, rotation=45, ha='right', fontsize=10)

lld_misses = tabela2['LLd misses'].values
cores_lld = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']
barras_lld = ax2.bar(algoritmos, lld_misses, color=cores_lld, alpha=0.8, edgecolor='black', linewidth=1.5)

ax2.set_ylabel('LLd Misses (Absoluto)', fontsize=12, fontweight='bold')
ax2.set_title('Faltas no Cache de Último Nível (Dados)', fontsize=13, fontweight='bold')
ax2.grid(True, alpha=0.3, axis='y')

for barra, valor in zip(barras_lld, lld_misses):
    altura = barra.get_height()
    ax2.text(barra.get_x() + barra.get_width()/2., altura,
             f'{int(valor):,}', ha='center', va='bottom', fontsize=9, fontweight='bold')

ax2.set_xticklabels(algoritmos, rotation=45, ha='right', fontsize=10)

plt.tight_layout()
plt.savefig('./auxiliar/02_grafico_cache_misses.png', dpi=300, bbox_inches='tight')
print('Gráfico salvo em: ./auxiliar/02_grafico_cache_misses.png')