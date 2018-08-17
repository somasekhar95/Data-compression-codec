# Data-compression-codec
Design and implementation of entropy encoding algorithms on multimedia data

Shannon-Fano - The Shannon-Fano encoder uses the top-down approach to construct the code tree when encoding. The code contains computation of entropy, relative frequency of symbols and the shannon-encoder based on global statistics.

Huffman Coding - The Huffman encoder uses the bottom-up approach to construct the code tree when encoding. For real-time
compression applications, we have to encode the symbols on the fly. The encoder/decoder will update the statistics of the symbol set and the coding table after encoding/decoding every symbol.

Run-length coding is one of the coding schemes that have been widely used. I've implemeted both the bassic and modified version of it.
