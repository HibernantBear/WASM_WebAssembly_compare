function lorenz_attractor(count, n, step = 0.1, init = [0.1, 0, 0]) {
  console.log("enter js");
  const buffer = new Array(n * 3);
  const a = 10,
    b = 8 / 3,
    c = 28;
  for (let i = 0; i < init.length; i++) {
    buffer[i] = init[i];
  }
  while (count > 0) {
    let i = 1 * 3;
    const _n = n * 3;
    while (i < _n) {
      const x = buffer[i - 3];
      const y = buffer[i - 2];
      const z = buffer[i - 1];
      buffer[i] = x + step * a * (y - x);
      buffer[i + 1] = y + step * (x * (c - z) - y);
      buffer[i + 2] = z + step * (x * y - b * z);
      i += 3;
    }
    for (let i = 0; i < 3; i++) {
      buffer[i] = buffer[3 * n - 3 + i];
    }
    count--;
  }
  console.log(n);
  return buffer;
}
