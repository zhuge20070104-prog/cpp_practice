# Git 工作流程指南

本文档介绍如何管理功能分支、压缩 commits 以及同步 main 分支的更新。

## 目录

- [快速参考](#快速参考)
- [核心概念](#核心概念)
- [常见场景](#常见场景)
- [详细操作](#详细操作)
- [命令对比](#命令对比)
- [故障排除](#故障排除)

---

## 快速参考

### 压缩多个 Commits 成一个

**方法 1：Reset（推荐，最简单）**
```bash
git checkout feature-branch
git reset --soft main
git commit -s -m "[TICKET] Feature description"
git push -f origin feature-branch
```

**方法 2：Interactive Rebase**
```bash
git rebase -i main
# 在编辑器中：第一行保持 pick，其余改为 s (squash)
# 保存后编辑 commit message
git push -f origin feature-branch
```

### 同步 Main 分支更新

**方法 1：Rebase（保持历史线性）**
```bash
git fetch origin main
git checkout main
git pull origin main
git checkout feature-branch
git rebase main
git push -f origin feature-branch
```

**方法 2：Reset（永远只有 1 个 commit）**
```bash
git fetch origin main
git checkout main
git pull origin main
git checkout feature-branch
git reset --soft main
git commit -s -m "[TICKET] Updated feature"
git push -f origin feature-branch
```

---

## 核心概念

### Reset vs Rebase

| 特性 | `git reset --soft main` | `git rebase main` |
|------|------------------------|-------------------|
| **操作方式** | 移动 HEAD 指针 | 重新应用 commits |
| **Commit 数量** | 需要手动创建 1 个 | 保持原有数量 |
| **需要 commit** | ✅ 是 | ❌ 否（自动） |
| **冲突处理** | 一次性（可能很大） | 分散在各个 commit |
| **开发历史** | 丢失 | 保留 |
| **Code Review** | 一次看完所有 | 可以分步查看 |
| **强制推送** | ✅ 必须 | ✅ 必须 |
| **适用场景** | 简单功能，频繁同步 | 复杂功能，保留历史 |

### Interactive Rebase 命令

| 命令 | 简写 | 作用 | Commit Message |
|------|------|------|---------------|
| `pick` | `p` | 保留这个 commit | 保留 |
| `squash` | `s` | 合并到上一个 commit | 保留，可编辑 |
| `fixup` | `f` | 合并到上一个 commit | 丢弃 |
| `drop` | `d` | 删除这个 commit | 删除 |
| `reword` | `r` | 保留 commit，修改 message | 可修改 |

---

## 常见场景

### 场景 1：初次创建 PR（压缩多个开发中的 commits）

**情况**：你有 100+ 个小 commits，想压缩成 1 个

**推荐方案**：Reset（最快）

```bash
# 1. 创建备份（以防万一）
git branch backup-feature-branch

# 2. 确保 main 是最新的
git fetch origin main
git checkout main
git pull origin main

# 3. 回到功能分支，压缩 commits
git checkout feature-branch
git reset --soft main

# 4. 查看状态（所有改动应该在暂存区）
git status

# 5. 创建新的 commit
git commit -s -m "[TICKET-123] Add feature XYZ

- Add core functionality
- Add tests and documentation
- Fix related issues"

# 6. 验证（应该只有 1 个 commit）
git log --oneline main..HEAD

# 7. 推送
git push -f origin feature-branch
```

### 场景 2：Main 有更新，需要同步

**情况**：你的 PR 已经提交，但 main 分支有了新的 commits

#### 选项 A：Rebase（如果想保持原有 commit 结构）

```bash
# 1. 更新 main
git fetch origin main
git checkout main
git pull origin main

# 2. Rebase 功能分支
git checkout feature-branch
git rebase main

# 3. 如果有冲突
#    - 解决冲突的文件
#    - git add <resolved-files>
#    - git rebase --continue
#    - 重复直到完成

# 4. 推送（需要强制推送）
git push -f origin feature-branch
```

#### 选项 B：Reset（如果每次都想只有 1 个 commit）

```bash
# 1. 更新 main
git fetch origin main
git checkout main
git pull origin main

# 2. 重新压缩（基于最新的 main）
git checkout feature-branch
git reset --soft main

# 3. 重新 commit
git commit -s -m "[TICKET-123] Add feature XYZ (updated)"

# 4. 推送
git push -f origin feature-branch
```

### 场景 3：保留几个关键 Commits（不是全部压缩成 1 个）

**情况**：你有 50 个 commits，想压缩成 3-5 个有意义的 commits

```bash
# 1. Interactive rebase
git rebase -i main

# 2. 在编辑器中，选择性地 squash：
pick abc123 Add core feature A
s def456 Fix bug in A
s ghi789 Improve A
pick jkl012 Add core feature B
s mno345 Optimize B
pick pqr678 Add documentation
s stu901 Fix typo in docs

# 3. 保存退出
# Git 会为每个 squash 组打开编辑器让你编辑 message

# 4. 推送
git push -f origin feature-branch
```

### 场景 4：恢复到压缩前的状态

**情况**：压缩错了，想恢复

```bash
# 1. 查看操作历史
git reflog -20

# 输出示例：
# abc1234 HEAD@{0}: commit: Squashed commit
# def5678 HEAD@{1}: reset: moving to main
# ghi9012 HEAD@{2}: commit: Last commit before reset  ← 这个！

# 2. 恢复到指定状态
git reset --hard HEAD@{2}
# 或者用具体的 hash
git reset --hard ghi9012

# 3. 验证
git log --oneline -10
```

### 场景 5：Rebase 遇到冲突

```bash
# Rebase 过程中遇到冲突
git rebase main

# 输出：
# CONFLICT (content): Merge conflict in file.py
# error: could not apply abc123...

# 解决方法：

# 选项 A：解决冲突（如果冲突不多）
# 1. 编辑冲突文件，解决冲突标记
vim file.py  # 删除 <<<<<<<, =======, >>>>>>> 标记

# 2. 标记为已解决
git add file.py

# 3. 继续 rebase
git rebase --continue

# 4. 可能还有更多冲突，重复步骤 1-3

# 选项 B：放弃 rebase，改用 reset（推荐）
git rebase --abort

# 然后用 reset 方法
git reset --soft main
git commit -s -m "message"
```

---

## 详细操作

### Vim 编辑器快速操作（用于 Interactive Rebase）

#### 快速替换 pick 为 squash
```vim
# 在编辑器中：
:%s/^pick/s/g       # 将所有 pick 替换为 s
:1s/^s/pick/        # 将第一行的 s 改回 pick
:wq                 # 保存并退出
```

#### 快速替换 pick 为 fixup
```vim
:%s/^pick/f/g       # 将所有 pick 替换为 f
:1s/^f/pick/        # 将第一行的 f 改回 pick
:wq
```

#### 编辑 Squash Message
```vim
# 删除所有旧的 messages，重写新的：
:%d                 # 删除所有行
i                   # 进入插入模式
# 输入新的 commit message
<Esc>               # 退出插入模式
:wq                 # 保存并退出
```

#### Vim 基础命令
```vim
i           # 进入插入模式（编辑）
<Esc>       # 退出插入模式，进入命令模式
:w          # 保存
:q          # 退出
:wq         # 保存并退出
:q!         # 不保存，强制退出
dd          # 删除当前行
:%d         # 删除所有行
u           # 撤销
```

### 验证操作结果

```bash
# 查看相对于 main 的 commits
git log --oneline main..HEAD

# 查看改动的文件统计
git diff --stat main

# 查看具体改动
git diff main

# 查看最后一个 commit 的详细信息
git log -1 --format=full

# 检查是否有 Signed-off-by
git log -1 | grep "Signed-off-by"

# 查看工作区状态
git status
```

---

## 命令对比

### 创建 Commit 的不同方式

| 场景 | 命令 | 结果 |
|------|------|------|
| 正常提交 | `git commit -m "msg"` | 1 个新 commit |
| 签名提交 | `git commit -s -m "msg"` | 1 个新 commit（带 Signed-off-by） |
| 修改最后一个 commit | `git commit --amend` | 修改最后的 commit |
| 添加签名到最后的 commit | `git commit --amend -s --no-edit` | 给最后的 commit 加签名 |

### Reset 的三种模式

| 模式 | 工作区 | 暂存区 | Commits | 常用场景 |
|------|-------|--------|---------|---------|
| `--soft` | 保留 | 保留（staged） | 移除 | **压缩 commits** |
| `--mixed`（默认） | 保留 | 清空 | 移除 | 取消暂存 |
| `--hard` | 清空 | 清空 | 移除 | ⚠️ 完全回滚（危险） |

```bash
# Soft reset - 只移动 HEAD，改动在暂存区
git reset --soft HEAD~3
git status  # Changes to be committed: ...

# Mixed reset - 移动 HEAD，改动在工作区（未暂存）
git reset HEAD~3
git status  # Changes not staged for commit: ...

# Hard reset - 完全丢弃改动（危险！）
git reset --hard HEAD~3
git status  # nothing to commit, working tree clean
```

### 推送方式

```bash
# 普通推送
git push origin feature-branch

# 强制推送（改写历史后）
git push -f origin feature-branch

# 强制推送（更安全，只在远程没有新 commits 时才推送）
git push --force-with-lease origin feature-branch

# 推送并设置上游分支
git push -u origin feature-branch
```

---

## 故障排除

### 问题 1：执行 reset 后发现改动丢失了

**原因**：可能用了 `--hard` 而不是 `--soft`

**解决**：
```bash
# 查看 reflog
git reflog

# 找到 reset 前的状态，恢复
git reset --hard HEAD@{1}
```

### 问题 2：Rebase 遇到太多冲突

**解决**：
```bash
# 放弃 rebase
git rebase --abort

# 改用 reset 方法
git reset --soft main
git commit -s -m "message"
```

### 问题 3：强制推送失败

**错误信息**：`! [rejected] feature-branch -> feature-branch (fetch first)`

**原因**：远程分支有你本地没有的 commits

**解决**：
```bash
# 查看远程分支状态
git fetch origin
git log HEAD..origin/feature-branch

# 如果确定要覆盖远程
git push -f origin feature-branch

# 或者用更安全的方式
git push --force-with-lease origin feature-branch
```

### 问题 4：忘记添加 Signed-off-by

**解决**：
```bash
# 给最后一个 commit 添加签名
git commit --amend --signoff --no-edit

# 或简写
git commit --amend -s --no-edit

# 推送
git push -f origin feature-branch
```

### 问题 5：压缩后发现 main 不是最新的

**解决**：
```bash
# 恢复到压缩前
git reflog
git reset --hard HEAD@{1}  # 找到压缩前的状态

# 更新 main
git checkout main
git pull origin main

# 重新压缩
git checkout feature-branch
git reset --soft main
git commit -s -m "message"
```

### 问题 6：不小心压缩了错误的分支

**解决**：
```bash
# 立即查看 reflog
git reflog

# 恢复到操作前
git reset --hard HEAD@{N}  # N 是 reflog 中的编号

# 切换到正确的分支
git checkout correct-branch
```

---

## 推荐工作流程

### 日常开发流程

```bash
# 1. 从最新 main 创建功能分支
git checkout main
git pull origin main
git checkout -b feature/new-feature

# 2. 正常开发，频繁小步提交
git add .
git commit -m "work in progress"
# ... 继续开发 ...

# 3. 完成开发，准备提交 PR
# 更新 main
git checkout main
git pull origin main

# 4. 压缩所有 commits 成一个
git checkout feature/new-feature
git reset --soft main
git commit -s -m "[TICKET-123] Add new feature

- Detailed description of changes
- Add tests
- Update documentation"

# 5. 推送并创建 PR
git push origin feature/new-feature
```

### PR 已提交，Main 又有更新

```bash
# 方法 A：如果只想保持 1 个 commit（推荐）
git fetch origin main
git checkout main
git pull origin main
git checkout feature/new-feature
git reset --soft main
git commit -s -m "[TICKET-123] Add new feature (updated)"
git push -f origin feature/new-feature

# 方法 B：如果想保持原有的 commit 结构
git fetch origin main
git checkout main
git pull origin main
git checkout feature/new-feature
git rebase main
git push -f origin feature/new-feature
```

---

## 最佳实践

### ✅ 推荐

1. **每次准备提交 PR 前，先更新 main**
   ```bash
   git checkout main && git pull origin main
   ```

2. **为重要操作创建备份分支**
   ```bash
   git branch backup-before-squash
   ```

3. **使用 `--force-with-lease` 而不是 `-f`（更安全）**
   ```bash
   git push --force-with-lease origin feature-branch
   ```

4. **写清晰的 commit message**
   ```
   [TICKET-123] Short summary (< 50 chars)

   - Detailed point 1
   - Detailed point 2
   - Detailed point 3

   Signed-off-by: Your Name <your.email@example.com>
   ```

5. **验证操作结果**
   ```bash
   git log --oneline main..HEAD  # 检查 commits
   git status                     # 检查工作区
   ```

### ❌ 避免

1. **不要在 main/master 分支上使用强制推送**
   ```bash
   # 危险！
   git push -f origin main
   ```

2. **不要在有其他人基于你的分支工作时强制推送**

3. **不要使用 `git reset --hard` 除非确定要丢弃改动**

4. **不要在没有备份的情况下做复杂操作**

5. **不要忽略 Git 的警告信息**

---

## 总结

### 什么时候用 Reset？

- ✅ 简单功能，不需要详细的开发历史
- ✅ Main 分支频繁更新
- ✅ 想要最干净的历史（永远 1 个 commit）
- ✅ 避免处理复杂的 rebase 冲突

### 什么时候用 Rebase？

- ✅ 复杂功能，需要保留开发历程
- ✅ 多人协作的分支
- ✅ Code review 需要分步查看
- ✅ 可能需要 cherry-pick 某些功能

### 快速决策树

```
需要压缩 commits？
├─ 是 → 压缩成几个？
│      ├─ 1 个 → 用 reset --soft
│      └─ 多个 → 用 rebase -i
└─ 否 → 只需同步 main？
       ├─ 是 → 用 rebase main
       └─ 否 → 正常开发即可
```

---

## 参考链接

- [Git 官方文档 - Rebase](https://git-scm.com/docs/git-rebase)
- [Git 官方文档 - Reset](https://git-scm.com/docs/git-reset)
- [Atlassian Git Tutorial](https://www.atlassian.com/git/tutorials)

---

**最后更新**：2025-11-24

