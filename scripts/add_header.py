#!/usr/bin/env python3
import os
from datetime import datetime
from pathlib import Path


def get_header(file_path: Path, base_dir: Path, year: int, comment: str) -> str:
    """根据文件类型生成对应的头部信息"""
    try:
        rel_path = file_path.relative_to(base_dir).as_posix()
    except ValueError:
        rel_path = file_path.as_posix()

    return f"""{comment} SPDX-License-Identifier: GPL-3.0-or-later
{comment}
{comment} {rel_path}
{comment} Copyright (C) 2025-{year} ss
{comment}
"""


def has_existing_header(content: str) -> bool:
    """检查文件是否已经有SPDX头部"""
    return "SPDX-License-Identifier" in (content.lstrip().split("\n")[0] if content else "")


def strip_existing_header(content: str) -> str:
    """移除已有的头部（前5行）"""
    lines = content.splitlines()
    return "\n".join(lines[5:]) if len(lines) > 5 else content


def add_header_to_file(file_path: Path, header: str):
    """给文件添加头部信息"""
    try:
        content = file_path.read_text(encoding="utf-8")
    except (UnicodeDecodeError, Exception) as e:
        print(f"✗ 无法读取文件: {file_path.as_posix()}: {e}")
        return

    if has_existing_header(content):
        content = strip_existing_header(content)
        print(f"↻ {file_path.as_posix()} (重新生成头部)")
    else:
        print(f"✓ {file_path.as_posix()}")

    file_path.write_text(header + "\n" + content.lstrip(), encoding="utf-8")


def process_files(root_dir: Path, base_dir: Path, year: int, extensions: set, comment: str):
    """通用文件处理函数"""
    if not root_dir.exists():
        print(f"警告: 目录不存在: {root_dir}")
        return

    for file_path in root_dir.rglob("*"):
        if not file_path.is_file() or ".git" in file_path.parts:
            continue
        if file_path.suffix.lower() not in extensions:
            continue

        header = get_header(file_path, base_dir, year, comment)
        add_header_to_file(file_path, header)


def main():
    work_path = os.environ.get("WORKPATH")
    if not work_path:
        print("错误: 未设置 WORKPATH 环境变量")
        return

    base_dir = Path(work_path)
    if not base_dir.exists():
        print(f"错误: 工作目录不存在: {work_path}")
        return

    year = datetime.now().year

    tasks = [
        ("C/C++文件", base_dir / "engine" / "src", {".cpp", ".c", ".h", ".hpp", ".cc"}, "//"),
        ("Python文件", base_dir / "py_script" / "src", {".py"}, "#"),
        ("着色器文件", base_dir / "shaders", {".glsl", ".frag", ".vert", ".sc"}, "//"),
    ]

    for label, directory, exts, comment in tasks:
        print(f"处理{label}: {directory}")
        process_files(directory, base_dir, year, exts, comment)

    print("处理完成!")


if __name__ == "__main__":
    main()