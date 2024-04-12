# Use uma imagem base do Ubuntu

FROM ocaml/opam:ubuntu-lts-ocaml-5.1

USER root
# Evitar perguntas da interface de usuário ao instalar pacotes
ARG DEBIAN_FRONTEND=noninteractive

# RUN curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | sudo apt-key add -
# RUN echo "deb https://dl.yarnpkg.com/debian/ stable main" | sudo tee /etc/apt/sources.list.d/yarn.list

RUN apt-get update && apt-get install -y curl 

RUN curl -fsSL https://deb.nodesource.com/setup_18.x | bash -

# Atualizar a lista de pacotes e instalar dependências necessárias
RUN apt-get update && apt-get install -y \
    git \
    m4 \
    opam \
    make \
    nodejs \
    pkg-config \
    libssl-dev \
    libev-dev \
    libpcre3-dev \
    libgmp-dev \
    && rm -rf /var/lib/apt/lists/*

RUN npm install -g yarn

# Adicionar os arquivos do projeto ao container
COPY assets/ assets/
COPY templates/ templates/
COPY src/ src/
COPY full-stack-reasonml-advanced-sample.opam full-stack-reasonml-advanced-sample.opam
COPY webpack.config.js webpack.config.js
COPY dune-project dune-project
COPY dune dune
COPY package.json package.json
COPY yarn.lock yarn.lock

# Instalar as dependências do projeto
RUN yarn install

# Inicializar o ambiente opam
RUN opam init -y --disable-sandboxing

# Criar um switch opam usando a versão específica do OCaml
RUN opam switch create . 5.1.1 --deps-only --with-test -y
    
# Construir o projeto
# Substitua o comando abaixo pelo necessário para construir seu projeto, se diferente
RUN eval $(opam env) && \
    opam exec -- dune build --profile=prod @all

RUN yarn webpack --env production

# Expor a porta do servidor
EXPOSE 8000

# CMD ["opam" exec -- dune exec src/server/server.exe"]
CMD ["_build/default/src/server/server.exe"]
