import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('seaborn-v0_8-darkgrid')
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

caminho_excel = './documentos/tabelas_lab20260927.xlsx'

tabela3_o0 = pd.read_excel(caminho_excel, sheet_name='tabela3_o0')
tabela3_o3 = pd.read_excel(caminho_excel, sheet_name='tabela3_o3')

threads_o0 = tabela3_o0['Threads (p)'].values
eficiencia_padrao_o0 = (tabela3_o0['Eficiência Padrão (Ep)'].values * 100).astype(float)
eficiencia_bloco_o0 = (tabela3_o0['Eficiência Bloco (Ep)'].values * 100).astype(float)

largura = 0.35
x = np.arange(len(threads_o0))

barras1_padrao = ax1.bar(x - largura/2, eficiencia_padrao_o0, largura, label='Padrão -O0', color='#1f77b4', alpha=0.8, edgecolor='black', linewidth=1.5)
barras1_bloco = ax1.bar(x + largura/2, eficiencia_bloco_o0, largura, label='Bloco -O0', color='#ff7f0e', alpha=0.8, edgecolor='black', linewidth=1.5)

for barra in barras1_padrao:
    altura = barra.get_height()
    ax1.text(barra.get_x() + barra.get_width()/2., altura,
             f'{altura:.0f}%', ha='center', va='bottom', fontsize=9, fontweight='bold')

for barra in barras1_bloco:
    altura = barra.get_height()
    ax1.text(barra.get_x() + barra.get_width()/2., altura,
             f'{altura:.0f}%', ha='center', va='bottom', fontsize=9, fontweight='bold')

ax1.set_xlabel('Número de Threads', fontsize=12, fontweight='bold')
ax1.set_ylabel('Eficiência (%)', fontsize=12, fontweight='bold')
ax1.set_title('Eficiência de Paralelismo (-O0)', fontsize=13, fontweight='bold')
ax1.set_xticks(x)
ax1.set_xticklabels(threads_o0.astype(int), fontsize=10)
ax1.legend(fontsize=11, loc='best')
ax1.grid(True, alpha=0.3, axis='y')
ax1.set_ylim(0, 110)

threads_o3 = tabela3_o3['Threads (p)'].values
eficiencia_padrao_o3 = (tabela3_o3['Eficiência Padrão (Ep)'].values * 100).astype(float)
eficiencia_bloco_o3 = (tabela3_o3['Eficiência Bloco (Ep)'].values * 100).astype(float)

x_o3 = np.arange(len(threads_o3))

barras2_padrao = ax2.bar(x_o3 - largura/2, eficiencia_padrao_o3, largura, label='Padrão -O3', color='#1f77b4', alpha=0.8, edgecolor='black', linewidth=1.5)
barras2_bloco = ax2.bar(x_o3 + largura/2, eficiencia_bloco_o3, largura, label='Bloco -O3', color='#ff7f0e', alpha=0.8, edgecolor='black', linewidth=1.5)

for barra in barras2_padrao:
    altura = barra.get_height()
    ax2.text(barra.get_x() + barra.get_width()/2., altura,
             f'{altura:.0f}%', ha='center', va='bottom', fontsize=9, fontweight='bold')

for barra in barras2_bloco:
    altura = barra.get_height()
    ax2.text(barra.get_x() + barra.get_width()/2., altura,
             f'{altura:.0f}%', ha='center', va='bottom', fontsize=9, fontweight='bold')

ax2.set_xlabel('Número de Threads', fontsize=12, fontweight='bold')
ax2.set_ylabel('Eficiência (%)', fontsize=12, fontweight='bold')
ax2.set_title('Eficiência de Paralelismo (-O3)', fontsize=13, fontweight='bold')
ax2.set_xticks(x_o3)
ax2.set_xticklabels(threads_o3.astype(int), fontsize=10)
ax2.legend(fontsize=11, loc='best')
ax2.grid(True, alpha=0.3, axis='y')
ax2.set_ylim(0, 110)

plt.tight_layout()
plt.savefig('./auxiliar/03_grafico_eficiencia.png', dpi=300, bbox_inches='tight')
print('Gráfico salvo em: ./auxiliar/03_grafico_eficiencia.png')