FROM ubuntu:22.04

# ARG DEBIAN_FRONTEND=noninteractive
ENV LANG C.UTF-8
ENV LANGUAGE en_US:
ENV TZ Asia/Tokyo

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# 基本のインストール
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN apt-get update -y
RUN apt-get install -y zsh
RUN apt-get install -y time
RUN apt-get install -y tree
RUN apt-get install -y git
RUN apt-get install -y curl
RUN apt-get install -y nano
RUN apt-get install -y vim
RUN apt-get install -y tmux
RUN apt-get install -y ca-certificates

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# プロンプトの見た目をいい感じにする
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN curl -sS https://starship.rs/install.sh | sh -s -- --yes
RUN echo "eval \"\$(starship init zsh)\"" > /root/.zshrc

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# シェルを zsh にする
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN chsh -s /bin/zsh
CMD ["/bin/zsh"]

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
RUN echo "alias pypy=\"uv run --python pypy3.10 -q\"" >> /root/.zshrc

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
RUN uv tool install rime
RUN uv tool install statements-manager
