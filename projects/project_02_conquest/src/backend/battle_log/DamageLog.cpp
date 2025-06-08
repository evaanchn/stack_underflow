// Copyright 2025 stack_underflow CC-BY 4.0

#include "DamageLog.hpp"

DamageLog::DamageLog(const std::string action) : ActionLog(action), damage(0) {
}

void DamageLog::setDamage(size_t damage) {
  this->damage = damage;
}
size_t DamageLog::getDamage() const {
  return this->damage;
}
std::string DamageLog::toString() {
  return ActionLog::toString() + " | Damage: " + std::to_string(this->damage);
}

uint64_t DamageLog::iterationsMean(std::vector<DamageLog>& logs) {
  return ::iterationsMean<DamageLog>(logs);
}

long double DamageLog::durationMean(std::vector<DamageLog>& logs) {
  return ::durationMean<DamageLog>(logs);
}

uint64_t DamageLog::damageMean(std::vector<DamageLog>& logs) {
  uint64_t sum = 0;
  uint64_t mean = 0;
  if (logs.empty()) return 0;
  for (auto &log : logs) {
    sum += log.getDamage();
  }
  mean = sum / logs.size();
  return mean;
}

uint64_t DamageLog::damageMode(std::vector<DamageLog>& logs) {
  std::unordered_map<size_t, size_t> damageAparitions;
  if (logs.empty()) return 0;
  for (auto &log : logs) {
    size_t damage = log.getDamage();
    ++damageAparitions[damage];
  }
  uint64_t mode = 0;
  size_t maxAparitions = 0;
  for (auto [damage, aparitions] : damageAparitions) {
    if (aparitions > maxAparitions) {
      maxAparitions = aparitions;
      mode = damage;
    }
  }
  return mode;
}
