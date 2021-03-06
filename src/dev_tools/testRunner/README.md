## testRunner

Simple tool to test the API routes.

#### Usage

`Usage:`    testRunner [-m|-f|-c|-n|-o|-r|-v|-h]
`Purpose:`  Run TrueBlocks' test cases with options.

`Where:`

| Short Cut | Option | Description |
| -------: | :------- | :------- |
| -m | --mode <val> | determine which set of tests to run, one of [cmd*&#124;api&#124;both] |
| -f | --filter <val> | determine how long it takes to run tests, one of [fast*&#124;medi&#124;slow&#124;all] |
| -c | --clean | clean working folder before running tests |
| -n | --no_quit | do not quit testing on first error |
| -o | --no_post | do not complete the post processing step |
| -r | --report | display performance report to screen |
| -v | --verbose | set verbose level. Either -v, --verbose or -v:n where 'n' is level |
| -h | --help | display this help screen |