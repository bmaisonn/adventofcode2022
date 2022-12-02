def iter_file(path):
    with open(path) as f:
        for l in f:
            yield l.rstrip('\r\n')
