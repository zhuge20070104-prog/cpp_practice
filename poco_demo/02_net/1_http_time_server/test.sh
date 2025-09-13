#!/bin/bash
curl -X POST  -H "Content-Type: application/json"   \
      http://127.0.0.1:8090/json_read -d \
      '{"name":"ZhangSan", "age": 40, "job": "Software Engineer in Testing"}'