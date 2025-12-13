import numpy as np
import matplotlib.pyplot as plt

# 设置参数
a = 1.0  # 势阱宽度
hbar = 1.0  # 简化计算，取hbar=1
m = 1.0    # 粒子质量取1

# 创建x轴坐标
x_inside = np.linspace(0, a, 500)
x_left = np.linspace(-0.5, 0, 50)
x_right = np.linspace(a, a+0.5, 50)
x_full = np.concatenate([x_left, x_inside, x_right])

# 要画的能级
n_values = [1, 2, 3, 4]

plt.figure(figsize=(10, 8))

# 画势阱形状
plt.plot([-0.5, 0, 0, a, a, a+0.5], [10, 10, 0, 0, 10, 10], 
         'k-', linewidth=2, label='V(x)')

for n in n_values:
    # 能量值
    E = (n**2 * np.pi**2 * hbar**2) / (2 * m * a**2)
    
    # 波函数
    psi = np.sqrt(2/a) * np.sin(n * np.pi * x_inside / a)
    # 阱外波函数为0
    psi_left = np.zeros_like(x_left)
    psi_right = np.zeros_like(x_right)
    psi_full = np.concatenate([psi_left, psi, psi_right])
    
    # 将波函数上移E的高度，方便观看
    wave_shifted = psi_full + E
    
    # 画波函数（实线）
    plt.plot(x_full, wave_shifted, label=f'n={n}, E={E:.2f}')
    
    # 画概率密度（虚线，缩放到合适大小）
    prob = (2/a) * np.sin(n * np.pi * x_inside / a)**2
    prob_left = np.zeros_like(x_left)
    prob_right = np.zeros_like(x_right)
    prob_full = np.concatenate([prob_left, prob, prob_right])
    # 概率密度缩放到能量范围
    prob_scaled = prob_full * 2 + E - 1.5  # 缩放并向下偏移
    plt.plot(x_full, prob_scaled, '--', alpha=0.7)

# 标注
plt.xlabel('位置 x', fontsize=12)
plt.ylabel('能量 E / 波函数 ψ / 概率密度 |ψ|²', fontsize=12)
plt.title('一维无限深势阱的能级、波函数（实线）与概率密度（虚线）', fontsize=14)
plt.legend()
plt.grid(alpha=0.3)
plt.ylim(-0.5, 18)  # 根据能量调整

plt.tight_layout()
plt.show()