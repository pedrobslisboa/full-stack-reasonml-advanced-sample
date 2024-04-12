open Jest;

Expect.(
  describe("classNames", () => {
    test("must create classNames", () => {
      let str = Shared_js_demo.Utils.classNames(["a", "b", "c"]);

      expect(str) |> toBe("a b c");
    })
  })
);
