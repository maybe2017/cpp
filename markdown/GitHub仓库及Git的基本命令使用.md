### 一、关联远程仓库、及一些常用git命令

> 注意: 以下对github库的操作均用git协议进行，若需要推送，将本地机器生成的SSH Key公钥配置到github上即可。不要用Https(容易出现各种网络问题)。

#### 1. 添加远程仓库

```bash
# 将本地原来没有关联git的代码 使用github管理
# 1. github上创建一个新仓库
# 2. 将本地代码根目录 关联到这个新仓库
git remote add origin git@github.com:maybe2017/cpp.git

# 若不想用默认的origin主机名称，想使用其他主机名则用git clone -o指定
git clone -o origin_other git@github.com:maybe2017/cpp.git  
```

- 'origin' 是当前远程库的名字，是当运行 `git clone` 时默认的远程仓库名字。 (自动被Git命名为origin，也可以改成别的)
- 'master' 是运行 `git init` 时默认的起始分支名字，原因仅仅是它的广泛使用。(因为对黑人种族歧视的原因，现在github上默认改为了 'main')

#### 2. 强制更新当前分支名称

```bash
# 本地代码根目录关联git新仓库后，git本身默认创建本地master分支，方便后续追踪远程master分支，但是github现在默认是main分支
# 3. 所以需要此命令，将本地分支改名为main，后续方便使当前本地分支追踪远程main分支
git branch -M main
```

#### 3. 本地向远程分支推送

```bash
# 第一次
git push -u origin main

# 后续推送
git push origin main 

# 不加任何参数(常使用)，表示推送到origin远程库上的，当前分支对应的远程分支上
git push

实际格式: git push <远程主机名> <本地分支名>:<远程分支名>

# 下面两者等效
git push origin master 
git push origin master:master
```

- 如果当前分支与多个主机存在追踪关系，则可以使用 -u 参数指定一个默认主机，这样后面就可以不加任何参数使用`git push`，则是默认向origin远程库的main分支进行推送。

- 如果远程分支被省略，如上则表示将本地分支推送到与之存在追踪关系的远程分支（通常两者同名），如果该远程分支不存在，则会被新建。

- 如果当前分支与远程分支存在追踪关系，则本地分支和远程分支都可以省略，将当前分支推送到origin主机的对应分支。

  ```bash
  1. git push 后不加参数的时候，默认就是【git push origin 当前的分支名】
  2. 比如对本地的master分支执行git push，其实就是git push origin master，当然，如果远程仓库没有master这个分支的话，就会报错
  ```

  

#### 4. 新建分支

```bash
# 在当前分支的基础上，创建一个新分支
git checkout -b new-branch

# 在origin/master的基础上，创建一个新分支
git checkout -b new-branch origin/master 
```

#### 5. 更新本地仓库的远程分支

```bash
git fetch origin --prune 
git fetch <远程主机名>  将某个远程库的更新全部取回本地[更新本地仓库的远程分支]

# 将origin库所有远程分支更新到本地，同时删除所有远程仓库中已经不存在的分支
git remote update origin --prune  

git fetch --all
```

#### 6. 删除远程仓库

```bash
git remote rm origin  解除了本地和远程库的绑定关系
```

#### 7. 查看所有分支

```bash
git branch
git branch -a 包括本地和远程的
git branch -r 查看远程分支
```



#### 8. 删除本地的临时分支、远程分支

```bash
git branch -D new_branch
git push origin --delete serverfix
```



### 二、SSH、Https协议

#### 1.  Https协议的麻烦之处与解决方案

```bash
# 使用git管理代码时，当我们使用ssh-key 配置git仓库地址时，将本地机器生成的SSH Key公钥配置到github上即可，后续就可以使用ssh协议与远程仓库进行通信。
# 生成 SSH Key ==>  ~/.ssh/id_rsa.pub
ssh-keygen -t rsa -C "985962824@qq.com"

# 但是在使用Https协议与远程仓库通信时，每次都需要输入远程仓库的用户名及密码进行验证。这是因为http协议是无状态的，想要像ssh一样不用输入用户名密码与远程仓库通信是不可能的；解决方法就是git的凭据管理。
```

####  2. git的凭据管理

```bash
# 凭据示例: protocol=https host=https://example.com/foo.git username=mayu password=secr3t

# mac系统默认用的钥匙串，Windows可以下载Git Credential Manager for Windows

# 现在有一种方式，可以简化push/pull操作，不用与仓库通信时都需要进行验证。这个方法就是配置Git 的凭证系统，类似浏览器缓存: git config --global credebtial.helper [选择]
```



### 三、其他命令

#### 1. git config 配置或读取相应的工作环境变量

```bash
# 优先级: /etc/gitconfig  =>>  ~/.gitconfig  =>> 当前项目(工作目录)的Git目录中的.git/config文件
# 覆盖: .git/config 里的配置会覆盖 /etc/gitconfig 中的同名变量

# 配置用户信息（个人的用户名称和电子邮件地址）
git config --global user.name "mayu"
git config --global user.email 985962824@qq.com

# 用--global 改的就是~/.gitconfig  之后所有的项目都会默认使用这里配置的用户信息
# 不用则是设置保存在当前项目的 .git/config 文件里

# 查看及修改用户信息
git config --list
vim ~/.gitconfig
```

#### 2. git remote查看当前工作区的 git 远程仓库信息

```bash
# 查看当前工作目录关联的 远程仓库地址
git remote -v
git remote show origin
```

#### 3. git clone与git init的使用

```bash
# 如果远程库不存在，或者刚刚初始化，那么使用git init 配合 git remote 完成对仓库的创建及对远端仓库的连接。
# git init 用于在本地创建一个git仓库，执行后，会在该目录下创建一个 .git 目录，目录下包含 object、refs、HEAD 等 git 记录文件，以及适用于本项目的 config 文件
# 然后用git remote add 配置对远程仓库的关联
git remote add origin git@github.com:yourName/yourRepo.git
git commit -m "注释"
git push -u origin main

# git clone 命令可以从原本已经存在的远端仓库中，下载和创建为本地仓库（通常都是这样做，因为远程库已经存在）
# 这个命令会将远端仓库的代码以及 git 记录下载到本地，并创建为本地仓库。
git clone git@github.com:yourName/yourRepo.git
```

#### 4. checkout 与checkout -b 的区别

```bash
# 用 git checkout exits_branchName 切换到某一已存在的分支
一般用于项目开发时，不同分支之间的切换

# 用 git checkout -b new_branchName 基于当前分支内容，创建新分支并立即切换到该分支下
通常用于项目开发时，开发新功能时，就需要先在主分支上切一个feature功能分支出来，开发测试结束后，再合并到主分支
```

#### 5. git stash的使用场景

假设在开发过程中，在当前分支上（dev1）已经写了一部分代码，没写完，暂时还不想提交。但是需要紧急切换到别的分支(dev2)上修改某个代码、或者做一些事，这时候不能直接从dev1分支上切换到dev2分支上。这时候怎么办？

```bash
# 可以通过git stash 在不提交代码的情况下能够临时保存dev1分支上的代码；然后切换到dev2分支上，等dev2分支上处理完成后，再切换到dev1分支上继续工作

# 1. 在dev1分支，执行git stash，缓存当前分支的修改；并可以通过 save "自定义本次暂存提示" 追加注释
git stash
# 2. 切换到dev2分支，做需要做的事情，做完之后切回dev1分支
# 3. 在dev1分支，执行git stash apply 应用缓存的修改；默认是使用第一个缓存，即stash@{0}
git stash apply
```






