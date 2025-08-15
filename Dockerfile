# Use official GCC image
FROM gcc:latest

# Set working directory inside container
WORKDIR /app

# Copy everything including the Hospital folder
COPY . .

# Compile the C++ file inside Hospital folder
RUN g++ Hospital/main.cpp -o Hospital/hospital

# Set working directory to Hospital
WORKDIR /app/Hospital

# Run the compiled executable
CMD ["./hospital"]
