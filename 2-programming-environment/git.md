# git

### 设置
```bash
git config --global user.name <name>
git config --global user.email <email>
# 设置当前仓库的用户名和email
git config user.name <name>
git config user.email <email>

# 或者直接开启一个编辑器
git config --global --edit

# 设置代理
git config --global http.proxy socks5://127.0.0.1:1080
git config --global --unset http.proxy
```

### 启动一个仓库
```bash
# 启动一个空白仓库
git init
# 获取远程仓库
git clone https://github.com/user/repo.git
```

### 基本流程
```bash
# 在一个已经存在的仓库
git status # 查看仓库状态
git add file_or_directory
git rm file_or_directory
git commit -m "message"
git push origin master # 远程服务器 origin 上的 master 分支
# 如果没有关联远程仓库
git remote add origin <server> # 这里的 origin 是 server 的代称，默认为origin
```

### 回到过去
```bash
# 查看提交历史
git log # 找出想要回到的提交
git reflog # checkout 前移HEAD后，HEAD之后的那些提交
git log --graph --pretty=oneline

# 设置HEAD的位置
git checkout master # 检出某个分支
git checkout <commit> # 检出某个提交，使用哈希串作为commit的id
git checkout <commit> <file> # 检出某个文件，不改变其它文件

git revert <commit> # 撤消某一次提交，如果有文件在该次提交之后又提交过，是发生冲突
git reset <commit> # 永远的撤销，危险的操作
git clean -f # 移除目录中未被跟踪的文件，-f参数只会列出会被删除的文件，但不实际执行
```

### 小的修改
```bash
# 重写提交，尤其是当提交后发现需要进行小的修改时，又不想做一个新的提交
git commit --amend
```

### 远程工作
```bash
# 查看远程连接
git remote
# 添加删除远程连接
git remote add <name> <repo>
git remote rm <name>
git remote rename <old-name> <new-name>

# 查看分支
git branch
# 创建和删除分支
git branch <branch-name>
git branch -d <branch-name>
git branch -D <branch-name> # 强制删除
# 合并某个分支到当前分支
git merge <branch-name>

# 拉取远程分支，fetch 不影响本地分支，用来查看远程分支的内容
git fetch <remote-name>
git fetch <remote-name> <branch>

# 拉取远程分支，并入本地分支
git pull <remote-name> # 相当于 fetch + merge
git pull --rebase <remote-name> # 使用 rebase 合并

# 推送到远程仓库
git push <remote-name> <branch>

# 当一个仓库被多个人拉取，提交修改时会使仓库的提交历史分叉。比如A在B提交修改前拉取，在B提交修改后提交，此时两个人在提交历史出现分歧。rebase可以将A提交修改的基础（拉取时的commit）修改到B提交修改后，使整个提交历史变为线性。
git pull
git rebase
git rebase -i # 交互式
```