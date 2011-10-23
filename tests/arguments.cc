
class Arguments {
public:
  Aplicacio(int argc, char *argv[]);

  int    num_arguments() const;
  string nom_programa() const;
  string argument(int n) const;
};

Arguments::Arguments(int argc, char *argv[]) {
  
}
