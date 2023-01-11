FROM python:3.11-slim as install

RUN apt-get update -y \
 && apt-get install -y --no-install-recommends -y build-essential \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

ENV PACKAGE=poetry-pybind11-integration \
    VERSION=0.3.1 \
    VENV=./venv

WORKDIR /app

COPY ./dist/$PACKAGE-$VERSION.tar.gz /app

RUN python -m venv $VENV
ENV PATH=$VENV/bin:$PATH
RUN pip install --no-cache-dir --upgrade pip $PACKAGE-$VERSION.tar.gz

FROM python:3.11-slim

ENV VENV=./venv

WORKDIR /app

# install as root...
COPY --from=install /app/$VENV /app/$VENV
COPY ./example.py .

# ...but don't run as root
RUN adduser --system --group app --no-create-home --disabled-password  # --shell /bin/false
USER app
ENV PATH=$VENV/bin:$PATH

CMD bash
