#include <string> 
#include <vector> 
#include <fstream> 
#include <iostream> 
#include <future> 
 
std::vector<char> readFile(const std::string& inPath) 
{ 
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "2 seconds have passed" << std::endl;
    std::ifstream file(inPath, std::ios::binary | std::ios::ate); 
    size_t length = (size_t)file.tellg(); 
    std::vector<char> buffer(length); 
    file.seekg(0, std::ios::beg); 
    file.read(&buffer[0], length); 
    std::cout << "finished reading" << std::endl;
    return buffer; 
} 
 
size_t writeFile(const std::vector<char>& buffer, const std::string& outPath) 
{ 
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "4 seconds have passed" << std::endl;
    std::ofstream file(outPath, std::ios::binary); 
    file.write(&buffer[0], buffer.size()); 
    std::cout << "finished writing" << std::endl;
    return (size_t)file.tellp(); 
}

size_t sync_copyFile(const std::string& inFile, const std::string& outFile) 
{ 
    return writeFile(readFile(inFile), outFile); 
}

size_t future_copyFile(const std::string& inFile, const std::string& outFile)
{
    std::cout << "setup reading" << std::endl;
    std::promise< std::vector<char> > promRead;
    std::future< std::vector<char> > futRead = promRead.get_future();
    std::thread thRead ([&promRead, inFile]() {
        promRead.set_value(readFile(inFile));
    });

    std::cout << "setup writing" << std::endl;
    std::promise<int> promWrite;
    std::future<int> futWrite = promWrite.get_future();
    std::thread thWrite ([&futRead, &promWrite, outFile]() {
        std::cout << "write will get the read" << std::endl;
        promWrite.set_value(writeFile(futRead.get(), outFile));
        std::cout << "write has got the read" << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "wait for the write to finish" << std::endl;
    size_t result = futWrite.get();
    thRead.join();
    thWrite.join();

    std::cout << "return the result" << std::endl;

    return result;
}

size_t async_copyFile(const std::string& inFile, const std::string& outFile) 
{
    auto futRead = async(readFile, inFile);
    auto futWrite = async([&futRead](const std::string& path) {
        return writeFile(futRead.get(), path);
    }, outFile);

    return futWrite.get();
}


int main()
{
    // sync_copyFile("abc.txt", "def.txt");
    // future_copyFile("abc.txt", "def.txt");
    async_copyFile("abc.txt", "def.txt");
}

