#!/usr/bin/env python3
import os
import subprocess
import sys
from pathlib import Path

PRESETS: list = ["debug", "release"]


def get_build_dir() -> Path:
    """获取BUILD_DIR环境变量 不存在则报错退出"""
    name = os.environ.get("BUILD_DIR")
    if not name:
        print("错误：环境变量 BUILD_DIR 未设置", file=sys.stderr)
        sys.exit(1)
    return Path(name)


def get_workpath() -> Path:
    """获取 WORKPATH 环境变量，不存在则报错退出"""
    workpath_str = os.environ.get("WORKPATH")
    if not workpath_str:
        print("错误：环境变量 WORKPATH 未设置", file=sys.stderr)
        sys.exit(1)
    return Path(workpath_str)


def get_project_name() -> str:
    """获取 PJ_NAME 环境变量，不存在则报错退出"""
    name = os.environ.get("PJ_NAME")
    if not name:
        print("错误：环境变量 PJ_NAME 未设置", file=sys.stderr)
        sys.exit(1)
    return name


def read_current_preset(preset_path: Path) -> str:
    """读取当前预设"""
    return preset_path.read_text().strip()


def select_new_preset() -> str:
    """让用户选择新预设"""
    print("可用预设:")
    for i, p in enumerate(PRESETS):
        print(f"[{i}] {p}")

    try:
        choice = int(input("选择: "))
    except ValueError:
        print("请输入有效数字", file=sys.stderr)
        sys.exit(1)

    if not (0 <= choice <= len(PRESETS) - 1):
        print("请输入有效数字", file=sys.stderr)
        sys.exit(1)

    return PRESETS[choice]


def write_preset_file(preset_path: Path, new_preset: str):
    """写入新预设到 .preset 文件"""
    preset_path.write_text(new_preset)


def write_launch_json(
    launch_path: Path, project_name: str, new_preset: str, build_dir: Path
):
    """生成并写入 launch.json"""
    program_path = build_dir / new_preset / project_name

    content = f"""{{
    "version": "0.2.0",
    "configurations": [
        {{
            "name": "引擎调试",
            "type": "cppdbg",
            "request": "launch",
            "program": "{program_path}",
            "args": [],
            "cwd": "${{workspaceFolder}}",
            "preLaunchTask": "cmake: build"
        }}
    ]
}}
"""
    launch_path.write_text(content)


def update_compile_commands(new_preset: str, build_dir: Path, engine_dir: Path):
    """更新 compile_commands.json 软链接"""
    src = build_dir / new_preset / "compile_commands.json"
    dst = engine_dir / "compile_commands.json"
    subprocess.run(["ln", "-sf", str(src), dst], check=True)


def main():
    workpath = get_workpath()
    project_name = get_project_name()
    build_dir = get_build_dir()

    engine_dir = workpath / "engine"
    os.chdir(str(engine_dir))

    preset_path = engine_dir / ".preset"
    launch_path = engine_dir / ".vscode" / "launch.json"

    current = read_current_preset(preset_path)
    print(f"当前预设: {current}")

    new_preset = select_new_preset()
    write_preset_file(preset_path, new_preset)
    write_launch_json(launch_path, project_name, new_preset, build_dir)
    update_compile_commands(new_preset, build_dir, engine_dir)

    print(f"已切换到预设: {new_preset}")


if __name__ == "__main__":
    main()
