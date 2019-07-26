{
  "targets": [
    {
      "target_name": "main",
      "sources": [
        "addon/main.cpp"
      ],
      "include_dirs" : [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'conditions': [
        ['OS=="win"', {
          'defines': [
            'PSK="<!(echo %PSK%)"',
            'PSKSALT="<!(echo %PSKSALT%)"'
          ]
        }],
        ['OS!="win"', {
          'defines': [
            'PSK="<!(echo $PSK)"',
            'PSKSALT="<!(echo $PSKSALT)"'
          ]
        }]
      ]
    }
  ]
}