
int main() 
{
  long a = 0;
  for (int i = 0; i < 20000; i++) {
    for (int j = 0; j < 20000; j++) {
      a = a + (i - j);
    }
  }
}

// Local variables:
// compile-command: "gcc -o ef1 eficiencia1.cc -lstdc++"
// End:
