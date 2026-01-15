package com.example.iot_server.controller;

import com.example.iot_server.domain.SensorData;
import com.example.iot_server.domain.SensorRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.List;

@RestController // "여기는 API 요청 받는 곳입니다"
@RequestMapping("/api/sensor") // 공통 주소: localhost:8080/api/sensor
public class SensorController {

    @Autowired
    private SensorRepository sensorRepository;

    // 1. 데이터 저장 (POST 요청)
    // 아두이노가 보낼 때 여기로 보냄
    @PostMapping
    public SensorData saveSensor(@RequestBody SensorData data) {
        data.setCreatedAt(LocalDateTime.now()); // 시간은 서버가 찍어줌
        return sensorRepository.save(data); // DB 저장!
    }

    // 2. 전체 데이터 조회 (GET 요청)
    // 앱이나 웹에서 확인할 때 사용
    @GetMapping
    public List<SensorData> getAllSensors() {
        return sensorRepository.findAll();
    }
}