# 使用 ubuntu 作为基础镜像
FROM ubuntu:20.04

# 更新 apt 并安装必要的软件包
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# 安装 Jupyter Notebook
RUN pip3 install --upgrade pip && \
    pip3 install jupyter

ENV LANG=C.UTF-8

# 创建工作目录
WORKDIR /notebooks

# 暴露 Jupyter Notebook 端口
EXPOSE 8888

# 启动 Jupyter Notebook
CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--no-browser", "--allow-root"]
