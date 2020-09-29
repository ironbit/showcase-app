# Build the docker image from the Dockerfile.
# path: in typeahead-golang folder
# exec: docker build -f docker/Dockerfile -t app-web .
#
# Load the docker container  from the image.
# docker run -p 12345:12345 app-web
FROM golang:alpine

# Set necessary environmet variables needed for our image
ENV PORT=12345 \
    FILE_NAME=names.json \
    SUGGESTION_NUMBER=5

# Move to working directory /build
WORKDIR /build

# Copy and download dependency using go mod
COPY app/go.mod .
COPY app/go.sum .
RUN go mod download

# Copy the code into the container
COPY app .

# Build the application
RUN go build -o app main/main.go

# Move to /deploy directory as the place for resulting binary folder
WORKDIR /deploy

# Copy binary from build to main folder
RUN cp /build/app .
ADD data/names.json .

# Export necessary port
EXPOSE $PORT

# Command to run when starting the container
CMD ["/deploy/app"]
