{
    "targets": [
        {
            "target_name": "xml2json",
            "sources": [
                "src/addon.cc",
                "src/tofile.cc",
                "src/tojson.cc",
                "src/include/xml2json.cc"
            ],
            "include_dirs": [
                "./src/include/",
                "<!(node -e \"require('nan')\")"
            ],
            "cflags": [ "-fno-rtti" ],
            "cflags_cc!": [ "-fno-rtti" ],
            "conditions": [
                ["OS==\"win\"", {

                }],
                ["OS==\"mac\"", {
                    "xcode_settings": {
                        "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
                    }
                }],
                ["OS==\"linux\"", {
                    "cflags!": [ "-fno-exceptions" ],
                    "cflags_cc!": [ "-fno-exceptions" ],
                }]
            ]
        }
    ]
}