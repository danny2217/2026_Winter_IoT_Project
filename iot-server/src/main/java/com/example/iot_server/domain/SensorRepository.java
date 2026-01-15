package com.example.iot_server.domain;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

// JpaRepository<엔터티이름, PK타입>
@Repository
public interface SensorRepository extends JpaRepository<SensorData, Long> {
    // 아무것도 안 적어도 save(), findAll(), findById() 다 됩니다. (JPA 매직)
}