FROM ubuntu:latest

RUN apt-get update && apt-get upgrade -y

# Install Valgrind
RUN apt-get install -y valgrind

WORKDIR /app

CMD ["sh"]


# to run
# should run in project directory
# docker run -it -v "$(pwd):/app" valgrind

# to build
# docker build -t valgrind .