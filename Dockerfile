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
RUN apt-get install -y ruby
RUN apt-get install -y ca-certificates

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# プロンプトの見た目をいい感じにする
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN curl -sS https://starship.rs/install.sh | sh -s -- --yes
RUN echo "eval \"\$(starship init zsh)\"" >> /root/.zshrc
RUN echo "(cd /root/app && uv sync &> /dev/null)" >> /root/.zshrc

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# シェルを zsh にする
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN chsh -s /bin/zsh
CMD ["/bin/zsh"]

#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
# C++ の環境を整える
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN apt-get install -y software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get update
RUN apt-get install -y gcc-13
RUN apt-get install -y g++-13
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100
RUN update-alternatives --config gcc
RUN update-alternatives --config g++

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
# Python の環境を整える
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
RUN uv python install pypy-3.10.14
RUN uv tool install rime
RUN uv tool install statements-manager
