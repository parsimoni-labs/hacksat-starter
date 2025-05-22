# Provides the latest kraft binary based on official instructions.
# SEE: https://unikraft.org/docs/cli/install

FROM debian

RUN apt-get update && \
  apt-get install -y \
      ca-certificates \
      curl \
      gnupg \
      lsb-release

RUN mkdir -p /etc/apt/keyrings && \
  curl -fsSL https://deb.pkg.kraftkit.sh/gpg.key | \
    gpg --dearmor -o /etc/apt/keyrings/unikraft.gpg

RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/unikraft.gpg] https://deb.pkg.kraftkit.sh /" | \
  tee /etc/apt/sources.list.d/unikraft.list > /dev/null
RUN apt-get update && apt-get install -y kraftkit

WORKDIR /mnt/build
ENTRYPOINT ["kraft"]

