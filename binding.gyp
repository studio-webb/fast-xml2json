{
    "targets": [
        {
            "target_name": "xml2json",
            "sources": [
                "src/xml2json.cc"
            ],
            "include_dirs": [
                "./src/include/"
            ],
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "cflags": [
                "-std=c++11",
                "-O3",
                "-fdata-sections",
                "-ffunction-sections"
            ],
            "conditions": [
                ["OS==\"win\"", {

                }],
                ["OS==\"mac\"", {
                    "xcode_settings": {
                        "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
                    }
                }]
            ]
        }
    ]
}