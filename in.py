import keyboard
import time

def keyboard_input():
    print("=" * 50)
    print("键盘输入 - keyboard库版本")
    print("=" * 50)

    round_count = 1

    while True:
        print(f"\n{'='*50}")
        print(f"第 {round_count} 轮输入")
        print(f"{'='*50}")

        print("\n请输入文字（输入 'END' 结束本轮，输入 'QUIT' 退出程序）：")
        lines = []
        while True:
            line = input()
            if line.strip() == 'END':
                break
            if line.strip() == 'QUIT':
                print("正在退出程序...")
                return
            lines.append(line)

        if not lines:  # 如果直接输入END，没有有效内容
            print("⚠️ 本轮没有输入任何内容")
        else:
            text = '\n'.join(lines)
            print(f"\n✓ 已接收 {len(text)} 个字符")
            print("\n⏰ 5秒后开始输入，请点击微信输入框！")

            for i in range(5, 0, -1):
                print(f"  {i}...", end='\r')
                time.sleep(1)

            print("\n▶ 开始输入...")

            try:
                keyboard.write(text, delay=0.05)
                print("✅ 本轮完成！")
            except Exception as e:
                print(f"❌ 错误: {e}")
                print("提示：可能需要管理员权限运行")

        # 询问是否继续
        print(f"\n第 {round_count} 轮结束")
        input("按回车键开始下一轮输入...")
        round_count += 1

if __name__ == "__main__":
    keyboard_input()