import pandas as pd
import matplotlib.pyplot as plt

plt.style.use('seaborn-v0_8-darkgrid')
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

caminho_excel = './documentos/tabelas_lab20260927.xlsx'

tabela3_o0 = pd.read_excel(caminho_excel, sheet_name='tabela3_o0')
tabela3_o3 = pd.read_excel(caminho_excel, sheet_name='tabela3_o3')

threads_o0 = tabela3_o0['Threads (p)'].values
speedup_padrao_o0 = tabela3_o0['Speedup Padrão (Sp\u200b)'].values
speedup_bloco_o0 = tabela3_o0['Speedup Bloco (Sp)'].values

ax1.plot(threads_o0, speedup_padrao_o0, 'o-', linewidth=2.5, markersize=9, label='Padrão -O0', color='#1f77b4')
ax1.plot(threads_o0, speedup_bloco_o0, 's-', linewidth=2.5, markersize=9, label='Bloco -O0', color='#ff7f0e')
ax1.set_xlabel('Número de Threads', fontsize=12, fontweight='bold')
ax1.set_ylabel('Speedup', fontsize=12, fontweight='bold')
ax1.set_title('Speedup vs Threads (-O0)', fontsize=13, fontweight='bold')
ax1.legend(fontsize=11, loc='best')
ax1.grid(True, alpha=0.3)
ax1.set_xticks(threads_o0)

threads_o3 = tabela3_o3['Threads (p)'].values
speedup_padrao_o3 = tabela3_o3['Speedup Padrão (Sp\u200b)'].values
speedup_bloco_o3 = tabela3_o3['Speedup Bloco (Sp)'].values

ax2.plot(threads_o3, speedup_padrao_o3, 'o-', linewidth=2.5, markersize=9, label='Padrão -O3', color='#1f77b4')
ax2.plot(threads_o3, speedup_bloco_o3, 's-', linewidth=2.5, markersize=9, label='Bloco -O3', color='#ff7f0e')
ax2.set_xlabel('Número de Threads', fontsize=12, fontweight='bold')
ax2.set_ylabel('Speedup', fontsize=12, fontweight='bold')
ax2.set_title('Speedup vs Threads (-O3)', fontsize=13, fontweight='bold')
ax2.legend(fontsize=11, loc='best')
ax2.grid(True, alpha=0.3)
ax2.set_xticks(threads_o3)

plt.tight_layout()
plt.savefig('./auxiliar/01_grafico_speedup.png', dpi=300, bbox_inches='tight')
print('Gráfico salvo em: ./auxiliar/01_grafico_speedup.png')