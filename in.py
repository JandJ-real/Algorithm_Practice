import keyboard
import time

def keyboard_input():
    print("=" * 50)
    print("键盘输入 - keyboard库版本")
    print("=" * 50)

    print("\n请输入文字（输入 'END' 结束）：")
    lines = []
    while True:
        line = input()
        if line.strip() == 'END':
            break
        lines.append(line)

    text = '\n'.join(lines)

    print(f"\n✓ 已接收 {len(text)} 个字符")
    print("\n⏰ 5秒后开始输入，请点击微信输入框！")

    for i in range(5, 0, -1):
        print(f"  {i}...", end='\r')
        time.sleep(1)

    print("\n▶ 开始输入...")

    try:
        keyboard.write(text, delay=0.05)
        print("✅ 完成！")
    except Exception as e:
        print(f"❌ 错误: {e}")
        print("提示：可能需要管理员权限运行")

    input("\n按回车退出...")

if __name__ == "__main__":
    keyboard_input()