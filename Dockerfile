FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Tokyo

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# 基本のインストール
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN apt-get update -y
RUN apt-get install -y \
    zsh \
    time \
    tzdata \
    tree \
    git \
    curl \
    ca-certificates

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# シェルを zsh にする
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN chsh -s /bin/zsh

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# C++ の環境を整える
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN apt-get update && \
    apt-get install -y g++

# ac-library
RUN git clone https://github.com/atcoder/ac-library.git /lib/ac-library
ENV CPLUS_INCLUDE_PATH /lib/ac-library

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# uv のインストール
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
ADD https://astral.sh/uv/install.sh /uv-installer.sh
RUN sh /uv-installer.sh && rm /uv-installer.sh
ENV PATH="/root/.local/bin/:$PATH"

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# 作業ディレクトリに移動して、
# 作問リポジトリをコピー
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
WORKDIR /app
COPY . /app

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# Python の環境を整える
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN uv python install pypy-3.10.14
RUN uv sync
