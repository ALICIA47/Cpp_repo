import os
import sys

def batch_rename_to_cpp(directory_path):
    """
    将指定目录下的所有文件后缀改为.cpp
    """

    if not os.path.exists(directory_path):
        print(f"错误：目录 '{directory_path}' 不存在！")
        return False
    
    if not os.path.isdir(directory_path):
        print(f"错误：'{directory_path}' 不是一个有效的目录！")
        return False

    renamed_count = 0
    skipped_count = 0
    
    try:
        for filename in os.listdir(directory_path):
            file_path = os.path.join(directory_path, filename)
            

            if os.path.isdir(file_path):
                continue

            file_name, file_extension = os.path.splitext(filename)

            if file_extension.lower() == '.cpp':
                print(f"跳过：'{filename}' 已经是.cpp文件")
                skipped_count += 1
                continue

            new_filename = file_name + '.cpp'
            new_file_path = os.path.join(directory_path, new_filename)

            if os.path.exists(new_file_path):
                print(f"警告：'{new_filename}' 已存在，跳过 '{filename}'")
                skipped_count += 1
                continue
            
            try:
                os.rename(file_path, new_file_path)
                print(f"成功：'{filename}' → '{new_filename}'")
                renamed_count += 1
            except Exception as e:
                print(f"错误：重命名 '{filename}' 失败 - {str(e)}")
                skipped_count += 1
    
    except Exception as e:
        print(f"处理目录时发生错误：{str(e)}")
        return False
    
    print(f"\n处理完成！")
    print(f"成功重命名：{renamed_count} 个文件")
    print(f"跳过的文件：{skipped_count} 个文件")
    return True

def main():

    target_directory = r"C:\diskD\C++\leetcode"
    
    print("=" * 50)
    print("文件后缀批量修改工具")
    print("=" * 50)
    print(f"目标目录：{target_directory}")
    print("将把所有文件的后缀改为 .cpp")
    print("=" * 50)

    response = input("确定要继续吗？(y/N): ").strip().lower()
    if response != 'y':
        print("操作已取消")
        return

    success = batch_rename_to_cpp(target_directory)
    
    if success:
        print("\n操作完成！按任意键退出...")
    else:
        print("\n操作失败！按任意键退出...")
    
    input()

if __name__ == "__main__":
    main()