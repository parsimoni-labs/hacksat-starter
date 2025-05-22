FROM ocaml/opam:debian-ocaml-5.3 as petrel_build
RUN sudo ln -f /usr/bin/opam-2.3 /usr/bin/opam
RUN cd ~/opam-repository && git pull origin master && git reset --hard da74d7829f794cc0af8b84981aff0c4d34114763
RUN opam update && opam install mirage.4.9.0
WORKDIR /mnt/build
COPY --chown=opam [ "./config.ml", "./config.ml" ]
RUN sudo chown -R opam:opam /mnt/build
RUN ls -alh /mnt/build
RUN opam exec -- mirage configure --config-file=./config.ml --target=hvt
# COPY --chown=opam [ "*.opam", "." ]
RUN opam exec -- make depend
RUN opam install solo5-cross-aarch64 ocaml-solo5-cross-aarch64
COPY --chown=opam [ ".", "." ]
RUN opam exec -- dune build --profile release --root . ./dist
RUN rm ./dist/dune; test 1 -eq $(ls ./dist | wc -l)
WORKDIR /mnt/output
RUN sudo chown -R opam:opam /mnt/output
RUN mv /mnt/build/./dist/* image
RUN aarch64-linux-gnu-strip -s image
